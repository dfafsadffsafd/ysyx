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

#include <cpu/cpu.h>  // 包含 CPU 相关的头文件

void sdb_mainloop();  // 声明简单调试器的主循环函数

void engine_start() {
#ifdef CONFIG_TARGET_AM  // 如果定义了 CONFIG_TARGET_AM（自动化机器目标）
  cpu_exec(-1);  // 执行 CPU 直到遇到错误或中止（-1 表示无限制运行）
#else  // 否则
  /* 接受用户的命令。 */
  sdb_mainloop();  // 进入简单调试器的主循环，接受并处理用户命令
#endif  // 结束条件编译
}

