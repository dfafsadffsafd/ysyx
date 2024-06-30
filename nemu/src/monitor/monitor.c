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
#include <memory/paddr.h>

// 函数显然是用于初始化各种系统模块或组件，当一个函数不需要返回值时，可以将其返回类型声明为 void
void init_rand();  // 初始化随机数生成器
void init_log(const char *log_file);  // 初始化日志系统
void init_mem();  // 初始化内存系统
void init_difftest(char *ref_so_file, long img_size, int port);  // 初始化差分测试模块
void init_device();  // 初始化设备
void init_sdb();  // 初始化简单调试器
void init_disasm(const char *triple);  // 初始化反汇编器

static void welcome() {
  Log("Trace: %s", MUXDEF(CONFIG_TRACE, ANSI_FMT("ON", ANSI_FG_GREEN), ANSI_FMT("OFF", ANSI_FG_RED)));
  // 如果启用了跟踪，记录日志信息
  IFDEF(CONFIG_TRACE, Log("If trace is enabled, a log file will be generated "
        "to record the trace. This may lead to a large log file. "
        "If it is not necessary, you can disable it in menuconfig"));
  Log("Build time: %s, %s", __TIME__, __DATE__);  // 记录构建时间
  printf("Welcome to %s-NEMU!\n", ANSI_FMT(str(__GUEST_ISA__), ANSI_FG_YELLOW ANSI_BG_RED));  // 打印欢迎信息
  printf("For help, type \"help\"\n");  // 提示用户输入 help 获取帮助
  //Log("Exercise: Please remove me in the source code and compile NEMU again.");  // 练习：请删除这行代码并重新编译 NEMU
  // assert(0);  // 断言失败，程序中止
}

#ifndef CONFIG_TARGET_AM
#include <getopt.h>

void sdb_set_batch_mode();  // 设置简单调试器的批处理模式

// 静态变量，用于存储命令行参数的值
static char *log_file = NULL;  // 日志文件路径
static char *diff_so_file = NULL;  // 差分测试参考文件路径
static char *img_file = NULL;  // 镜像文件路径
static int difftest_port = 1234;  // 差分测试端口，默认值为 1234

static long load_img() {
  if (img_file == NULL) {
    Log("No image is given. Use the default build-in image.");  // 没有提供镜像文件，使用内建镜像
    return 4096; // 内建镜像大小
  }

  FILE *fp = fopen(img_file, "rb");  // 打开镜像文件
  Assert(fp, "Can not open '%s'", img_file);  // 确认文件打开成功

  fseek(fp, 0, SEEK_END);  // 移动文件指针到文件末尾
  long size = ftell(fp);  // 获取文件大小

  Log("The image is %s, size = %ld", img_file, size);  // 记录镜像文件信息

  fseek(fp, 0, SEEK_SET);  // 移动文件指针到文件开头
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);  // 读取镜像文件到内存中
  assert(ret == 1);  // 确认读取成功

  fclose(fp);  // 关闭文件
  return size;  // 返回镜像文件大小
}

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {"batch"    , no_argument      , NULL, 'b'},  // 批处理模式
    {"log"      , required_argument, NULL, 'l'},  // 日志文件
    {"diff"     , required_argument, NULL, 'd'},  // 差分测试参考文件
    {"port"     , required_argument, NULL, 'p'},  // 差分测试端口
    {"help"     , no_argument      , NULL, 'h'},  // 帮助信息
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-bhl:d:p:", table, NULL)) != -1) {
    switch (o) {
      case 'b': sdb_set_batch_mode(); break;  // 设置批处理模式
      case 'p': sscanf(optarg, "%d", &difftest_port); break;  // 设置差分测试端口
      case 'l': log_file = optarg; break;  // 设置日志文件路径
      case 'd': diff_so_file = optarg; break;  // 设置差分测试参考文件路径
      case 1: img_file = optarg; return 0;  // 设置镜像文件路径并退出
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-b,--batch              run with batch mode\n");
        printf("\t-l,--log=FILE           output log to FILE\n");
        printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
        printf("\n");
        exit(0);  // 显示帮助信息并退出
    }
  }
  return 0;  // 返回
}

void init_monitor(int argc, char *argv[]) {
  /* Perform some global initialization. */
  // 解析命令行参数
  parse_args(argc, argv);

  // 设置随机数种子
  init_rand();

  // 打开日志文件
  init_log(log_file);

  // 初始化内存
  init_mem();

  // 初始化设备
  IFDEF(CONFIG_DEVICE, init_device());

  // 执行 ISA 相关的初始化
  init_isa();

  // 将镜像加载到内存，这会覆盖内建镜像
  long img_size = load_img();

  // 初始化差分测试
  init_difftest(diff_so_file, img_size, difftest_port);

  // 初始化简单调试器
  init_sdb();

#ifndef CONFIG_ISA_loongarch32r
  // 初始化反汇编器
  IFDEF(CONFIG_ITRACE, init_disasm(
    MUXDEF(CONFIG_ISA_x86,     "i686",
    MUXDEF(CONFIG_ISA_mips32,  "mipsel",
    MUXDEF(CONFIG_ISA_riscv,
      MUXDEF(CONFIG_RV64,      "riscv64",
                               "riscv32"),
                               "bad"))) "-pc-linux-gnu"
  ));
#endif

  // 显示欢迎信息
  welcome();
}
#else // CONFIG_TARGET_AM
static long load_img() {
  extern char bin_start, bin_end;
  size_t size = &bin_end - &bin_start;  // 获取镜像大小
  Log("img size = %ld", size);
  memcpy(guest_to_host(RESET_VECTOR), &bin_start, size);  // 将镜像复制到内存中
  return size;  // 返回镜像大小
}

void am_init_monitor() {
  init_rand();  // 初始化随机数生成器
  init_mem();  // 初始化内存
  init_isa();  // 初始化 ISA
  load_img();  // 加载镜像
  IFDEF(CONFIG_DEVICE, init_device());  // 初始化设备
  welcome();  // 显示欢迎信息
}
#endif

