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
//物理地址读入
#include <memory/host.h>
#include <memory/paddr.h>
#include <device/mmio.h>
#include <isa.h>

#if   defined(CONFIG_PMEM_MALLOC)
// 如果定义了 CONFIG_PMEM_MALLOC，则使用动态分配的物理内存
static uint8_t *pmem = NULL;
#else // CONFIG_PMEM_GARRAY
// 否则使用静态数组分配物理内存，大小为 CONFIG_MSIZE，并对齐到页边界
static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};
#endif

// 将客机（虚拟机）的物理地址转换为主机（宿主机）的地址
uint8_t* guest_to_host(paddr_t paddr) { return pmem + paddr - CONFIG_MBASE; }
// 将主机（宿主机）的地址转换为客机（虚拟机）的物理地址
paddr_t host_to_guest(uint8_t *haddr) { return haddr - pmem + CONFIG_MBASE; }

// 从物理内存中读取数据
static word_t pmem_read(paddr_t addr, int len) {
  word_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

// 向物理内存中写入数据
static void pmem_write(paddr_t addr, int len, word_t data) {
  host_write(guest_to_host(addr), len, data);
}

// 当地址超出物理内存范围时触发错误
static void out_of_bound(paddr_t addr) {
  panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
      addr, PMEM_LEFT, PMEM_RIGHT, cpu.pc);
}

// 初始化物理内存
void init_mem() {
#if   defined(CONFIG_PMEM_MALLOC)
  // 如果定义了 CONFIG_PMEM_MALLOC，则动态分配内存
  pmem = malloc(CONFIG_MSIZE);
  assert(pmem);
#endif
  // 如果定义了 CONFIG_MEM_RANDOM，则用随机值初始化内存
  IFDEF(CONFIG_MEM_RANDOM, memset(pmem, rand(), CONFIG_MSIZE));
  Log("physical memory area [" FMT_PADDR ", " FMT_PADDR "]", PMEM_LEFT, PMEM_RIGHT);
}

// 从物理地址读取数据
word_t paddr_read(paddr_t addr, int len) {
  if (likely(in_pmem(addr))) return pmem_read(addr, len); // 如果地址在物理内存范围内，读取数据
  IFDEF(CONFIG_DEVICE, return mmio_read(addr, len)); // 如果定义了 CONFIG_DEVICE，则从 MMIO 读取数据
  out_of_bound(addr); // 如果地址超出范围，触发错误
  return 0;
}

// 向物理地址写入数据
void paddr_write(paddr_t addr, int len, word_t data) {
  if (likely(in_pmem(addr))) { pmem_write(addr, len, data); return; } // 如果地址在物理内存范围内，写入数据
  IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return); // 如果定义了 CONFIG_DEVICE，则向 MMIO 写入数据
  out_of_bound(addr); // 如果地址超出范围，触发错误
}
