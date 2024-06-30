#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include <stdint.h>
#include <stdbool.h>

// 声明所有在watchpoint.c中定义并需要在其他文件中使用的函数
void info_watchpoint();
void init_wp_pool();
struct watchpoint *new_wp();
void free_wp(struct watchpoint *wp);
void wp_set(char *args, int32_t res);
void wp_remove(int no);
void wp_difftest();

#endif // __WATCHPOINT_H__
