/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/paddr.h>
#include "watchpoint.h"
static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;
  return -1;
}


//单部执行
static int cmd_si(char *args)
{
  int n;
  if (args==NULL){
    n=1;
  }
  else sscanf(args,"%d",&n);
  cpu_exec(n);
  return 0;
 
}

//打印程序状态
static int cmd_info(char *args){
  if (args==NULL){
    printf("\"r\"-Print register status  or  \"w\"-Print watchpoint information\n");
  }
  else if (strcmp(args, "r") == 0){
    //打印寄存器状态:
    isa_reg_display();
  }
  else if (strcmp(args,"w")==0)
  {
    //打印监视点状态
    info_watchpoint();
  }
 
  return 0;
}


//扫描内存
static int cmd_x(char *args){
  if (args == NULL) {
        printf("Wrong Command!\n");
        return 0;
    }                                                                           
	int N;// 要读取的 32 位值的数量
  uint32_t startAddress;
	sscanf(args,"%d%x",&N,&startAddress);
	for (int i = 0;i < N;i ++){
      printf("%x\n", paddr_read(startAddress, 4));
      //C语言会自动执行类型提升以匹配表达式的操作数的类型。所以，4 被转换为 uint32_t，
      // 将起始地址增加 4，以读取下一个 32 位值
      startAddress += 4;
  
  }
   return 0;
}

//解析并计算表达式
static int cmd_p(char *args){
  bool success=true;
  //解析并计算表达式，将结果存储在 res 变量中。如果解析失败，success 将被设置为 false。
  int32_t res = expr(args, &success);
  if (!success) 
  {
    printf("invalid expression\n");
  } else 
  {
    printf("%d\n", res);
  }
  return 0; 
}


// 设置监视点
static int cmd_w(char *args) {
  // 如果没有提供参数，打印使用说明
  if (!args) {
    printf("Usage: w EXPR\n"); // 打印用法说明
    return 0; // 返回0表示命令执行完成
  }
  
  bool success; // 定义布尔变量success用于表示表达式解析是否成功
  int32_t res = expr(args, &success); // 解析表达式并计算其值，结果存储在res中
  
  // 如果表达式解析失败，打印错误信息
  if (!success) {
    printf("invalid expression\n"); // 打印无效表达式错误信息
  } 
  else {
    wp_set(args, res); // 如果解析成功，设置监视点，传入表达式字符串和计算结果
  }
  
  return 0; // 返回0表示命令执行完成
}

// 删除序列号为N的监视点
static int cmd_d(char *args) {
  char *arg = strtok(NULL, ""); // 使用strtok函数分割参数，获取序列号字符串
  
  // 如果没有提供参数，打印使用说明
  if (!arg) {
    printf("Usage: d N\n"); // 打印用法说明
    return 0; // 返回0表示命令执行完成
  }
  
  int no = strtol(arg, NULL, 10); // 将序列号字符串转换为整数
  wp_remove(no); // 删除对应序列号的监视点
  
  return 0; // 返回0表示命令执行完成
}


static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "exec si", cmd_si },
  { "info", "reg status", cmd_info },
  { "x", "scan mem" , cmd_x },
  { "p", "expr value", cmd_p },
  {"w", "add watchpoint", cmd_w},
  {"d", "delete watchpoint", cmd_d},
  


  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
