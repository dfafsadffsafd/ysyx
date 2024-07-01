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

//宏定义用于防止头文件被多次包含。#ifndef 检查 __ISA_RISCV_H__ 是否未定义
#ifndef __ISA_RISCV_H__
#define __ISA_RISCV_H__

#include <common.h>

//定义一个 CPU 状态结构体，其中包含通用寄存器组（GPR）和程序计数器（PC）
typedef struct {
  word_t gpr[MUXDEF(CONFIG_RVE, 16, 32)];
  vaddr_t pc;
} MUXDEF(CONFIG_RV64, riscv64_CPU_state, riscv32_CPU_state);

// decode
//定义一个用于指令解码的结构体，其中包含一个 uint32_t 类型的联合体成员 val
typedef struct {
  union {
    uint32_t val;
  } inst;
} MUXDEF(CONFIG_RV64, riscv64_ISADecodeInfo, riscv32_ISADecodeInfo);

//检查虚拟地址（vaddr）的 MMU 状态
#define isa_mmu_check(vaddr, len, type) (MMU_DIRECT)

#endif
/*
word_t 和 uint32_t 都是类型定义，用于表示特定宽度的整数类型.
ord_t 通常是一个项目或库自定义的类型，表示计算机架构中的“字”大小。它的具体定义取决于目标平台的位宽（32位或64位
*/