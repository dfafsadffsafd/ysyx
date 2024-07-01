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

#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <locale.h>

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INST_TO_PRINT 10  // 执行指令数量少于该值时，汇编代码输出到屏幕

CPU_state cpu = {};  // 定义 CPU 状态结构体
uint64_t g_nr_guest_inst = 0;  // 记录执行的指令总数
static uint64_t g_timer = 0; // 计时器，以微秒为单位
static bool g_print_step = false;  // 是否打印每一步的执行信息

void device_update();  // 声明设备更新函数

// 追踪和差异测试函数
static void trace_and_difftest(Decode *_this, vaddr_t dnpc) {
#ifdef CONFIG_ITRACE_COND
  if (ITRACE_COND) { log_write("%s\n", _this->logbuf); }  // 条件满足时，写日志
#endif
  if (g_print_step) { IFDEF(CONFIG_ITRACE, puts(_this->logbuf)); }  // 打印执行步骤
  IFDEF(CONFIG_DIFFTEST, difftest_step(_this->pc, dnpc));  // 进行差异测试
}

// 执行一次指令
static void exec_once(Decode *s, vaddr_t pc) {
  s->pc = pc;  // 设置当前指令地址
  s->snpc = pc;  // 表示下一条指令的地址初始值。
  isa_exec_once(s);  // 该函数根据指令的类型和操作码对指令进行解码和执行。解码后的指令信息存储在 Decode 结构体 s 中
  cpu.pc = s->dnpc;  // 即解码后的下一条指令的地址赋值给 cpu.pc
//记录和打印指令执行日志（如果启用了指令跟踪）
#ifdef CONFIG_ITRACE
  char *p = s->logbuf;
  p += snprintf(p, sizeof(s->logbuf), FMT_WORD ":", s->pc);  // 记录当前指令地址
  int ilen = s->snpc - s->pc;  // 计算指令长度
  int i;
  uint8_t *inst = (uint8_t *)&s->isa.inst.val;
  for (i = ilen - 1; i >= 0; i --) {
    p += snprintf(p, 4, " %02x", inst[i]);  // 记录指令内容
  }
  int ilen_max = MUXDEF(CONFIG_ISA_x86, 8, 4);  // 根据 ISA 设置最大指令长度
  int space_len = ilen_max - ilen;  // 计算空格长度
  if (space_len < 0) space_len = 0;
  space_len = space_len * 3 + 1;
  memset(p, ' ', space_len);  // 填充空格
  p += space_len;

#ifndef CONFIG_ISA_loongarch32r
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);  // 声明反汇编函数
  disassemble(p, s->logbuf + sizeof(s->logbuf) - p,
      MUXDEF(CONFIG_ISA_x86, s->snpc, s->pc), (uint8_t *)&s->isa.inst.val, ilen);  // 反汇编指令
#else
  p[0] = '\0'; // 如果不支持 loongarch32r，则设置为空字符串
#endif
#endif
}

// 执行指定数量的指令
static void execute(uint64_t n) {
  Decode s;  // 定义解码结构体
  for (;n > 0; n --) {
    exec_once(&s, cpu.pc);  // 执行一条指令
    g_nr_guest_inst ++;  // 递增指令计数
    trace_and_difftest(&s, cpu.pc);  // 进行追踪和差异测试
    if (nemu_state.state != NEMU_RUNNING) break;  // 检查 NEMU 状态
    IFDEF(CONFIG_DEVICE, device_update());  // 更新设备状态
  }
}

// 统计函数
static void statistic() {
  IFNDEF(CONFIG_TARGET_AM, setlocale(LC_NUMERIC, ""));  // 设置本地化
#define NUMBERIC_FMT MUXDEF(CONFIG_TARGET_AM, "%", "%'") PRIu64  // 定义数字格式
  Log("host time spent = " NUMBERIC_FMT " us", g_timer);  // 输出主机时间
  Log("total guest instructions = " NUMBERIC_FMT, g_nr_guest_inst);  // 输出总指令数
  if (g_timer > 0) Log("simulation frequency = " NUMBERIC_FMT " inst/s", g_nr_guest_inst * 1000000 / g_timer);  // 输出模拟频率
  else Log("Finish running in less than 1 us and can not calculate the simulation frequency");  // 运行时间少于1微秒时的处理
}

// 断言失败消息
void assert_fail_msg() {
  isa_reg_display();  // 显示寄存器状态
  statistic();  // 输出统计信息
}

// 模拟 CPU 工作
void cpu_exec(uint64_t n) {
  g_print_step = (n < MAX_INST_TO_PRINT);  // 设置是否打印每一步
  ///检查 NEMU 状态
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");  // 如果程序已结束，提示重新运行
      return;
    default: nemu_state.state = NEMU_RUNNING;  // 否则，将状态设置为 NEMU_RUNNING，表示开始执行指令。

  uint64_t timer_start = get_time();  // 获取开始时间

  execute(n);  // 执行指令

  uint64_t timer_end = get_time();  // 获取结束时间
  g_timer += timer_end - timer_start;  // 更新计时器
  //更新 NEMU 状态和统计信息
  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;  // 如果状态为运行，设置为停止

    case NEMU_END: case NEMU_ABORT:
      Log("nemu: %s at pc = " FMT_WORD,
          (nemu_state.state == NEMU_ABORT ? ANSI_FMT("ABORT", ANSI_FG_RED) :
           (nemu_state.halt_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) :
            ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
          nemu_state.halt_pc);  // 输出 NEMU 状态信息
      // fall through
    case NEMU_QUIT: statistic();  // 输出统计信息
  }
}}
