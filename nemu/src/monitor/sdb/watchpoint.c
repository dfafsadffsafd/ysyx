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

#include "sdb.h"

// wp_pool 数组可以存储 NR_WP 个监视点结构体对象
#define NR_WP 32 // 定义监视点数量
 
typedef struct watchpoint {
  int NO; // 监视点编号
  struct watchpoint *next; // 指向下一个监视点的指针
  char *expression;  // 监视点的表达式
  int value;        // 监视点的上一个值
 
  /* TODO: Add more members if necessary */
 
} WP; // 定义监视点结构体
 
static WP wp_pool[NR_WP] = {}; // 定义一个监视点池，大小为 NR_WP
// head 用于组织使用中的监视点结构, free_ 用于组织空闲的监视点结构
static WP *head = NULL, *free_ = NULL; // 定义使用中和空闲的监视点链表
 
void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i++) { // 初始化监视点池
    wp_pool[i].NO = i; // 设置监视点编号
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]); // 链接监视点链表
  }
 
  head = NULL; // 初始化使用中链表为空
  free_ = wp_pool; // 初始化空闲链表指向监视点池
}
 
/* TODO: Implement the functionality of watchpoint */
 
// new_wp() 从 free_ 链表中返回一个空闲的监视点结构
WP* new_wp();
 
// free_wp() 将 wp 归还到 free_ 链表中
void free_wp(WP *wp);
 
WP* new_wp() {
  if (free_ == NULL) { // 如果没有空闲监视点
    printf("free_没有空闲监视点\n");
    assert(0); // 断言失败
  }  
  WP *pos = free_; // 从空闲链表中取出一个监视点
  free_++; // 移动空闲链表头指针
  pos->next = head; // 将新监视点插入使用中链表头部
  head = pos; // 更新使用中链表头指针
  return pos; // 返回新监视点
}
 
void free_wp(WP *wp) {
  if (wp == head) { // 如果要释放的监视点是使用中链表的头
    head = head->next; // 更新使用中链表头指针
  } else {
    WP *pos = head; // 遍历使用中链表，找到要释放的监视点
    while (pos && pos->next != wp) {
      pos++;
    }
    if (!pos) { // 如果没有找到
      printf("输入的监视点不在head链表中\n");
      assert(0); // 断言失败
    }
    pos->next = wp->next; // 从使用中链表中移除该监视点
  }
  wp->next = free_; // 将监视点加入空闲链表头部
  free_ = wp; // 更新空闲链表头指针
}
 
void info_watchpoint() {
  WP *pos = head; // 遍历使用中链表
  if (!pos) {
    printf("NO watchpoints"); // 如果没有监视点
    return;
  }
  printf("%-8s%-8s\n", "No", "Expression"); // 打印表头
  while (pos) {
    printf("%-8d%-8s\n", pos->NO, pos->expression); // 打印每个监视点的信息
    pos = pos->next; // 移动到下一个监视点
  }
}
 
void wp_set(char *args, int32_t res) {
  WP* wp = new_wp(); // 获取一个新的监视点
  strcpy(wp->expression, args); // 设置监视点的表达式
  wp->value = res; // 设置监视点的初始值
  printf("Watchpoint %d: %s\n", wp->NO, wp->expression); // 打印监视点信息
}
 
void wp_remove(int no) {
  if (no < 0 || no >= NR_WP) { // 检查监视点编号是否合法
    printf("N is not in right\n");
    assert(0); // 断言失败
  }
  WP* wp = &wp_pool[no]; // 获取要移除的监视点
  free_wp(wp); // 释放监视点
  printf("Delete watchpoint %d: %s\n", wp->NO, wp->expression); // 打印移除信息
}
 
void wp_difftest() {
  WP* pos = head; // 遍历使用中链表
  while (pos) {
    bool _; // 定义一个临时变量
    word_t new = expr(pos->expression, &_); // 计算监视点的当前值
    if (pos->value != new) { // 如果监视点的值发生变化
      printf("Watchpoint %d: %s\n"
        "Old value = %d\n"
        "New value = %d\n"
        , pos->NO, pos->expression, pos->value, new); // 打印变化信息
      pos->value = new; // 更新监视点的值
      nemu_state.state = NEMU_STOP; // 停止仿真
    }
    pos = pos->next; // 移动到下一个监视点
  }
}

