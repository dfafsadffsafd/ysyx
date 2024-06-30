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

#include <stdint.h> // 引入标准整数类型头文件
#include <stdio.h> // 引入标准输入输出头文件
#include <stdlib.h> // 引入标准库头文件
#include <time.h> // 引入时间库头文件
#include <assert.h> // 引入断言头文件
#include <string.h> // 引入字符串处理头文件

typedef uint32_t word_t; // 定义一个无符号32位整数类型
// 定义缓冲区，应该足够大
static char buf[65536] = {}; // 定义一个大小为65536的缓冲区
static char code_buf[65536 + 128] = {}; // 定义一个稍大于`buf`的缓冲区
static char *code_format =
"#include <stdio.h>\n" // 包含标准输入输出头文件
"int main() { " // 主函数开始
"  unsigned result = %s; " // 定义一个无符号整数结果，并使用格式化字符串填充表达式
"  printf(\"%%u\", result); " // 打印结果
"  return 0; " // 返回0
"}";

// 生成0到n-1之间的数
static word_t choose(word_t n)
{
  return rand() % n; // 返回0到n-1之间的随机数
}

// 生成一个随机数字
static void gen_num() {
    word_t num = rand() % 10; // 生成0到9之间的随机数
    char num_str[12]; // 定义一个临时缓冲区
    snprintf(num_str, sizeof(num_str), "%d", num); // 将数字转化为字符串
    if (strlen(buf) + strlen(num_str) < sizeof(buf)) { // 检查缓冲区是否有足够空间
        strcat(buf, num_str); // 将数字字符串添加到缓冲区末尾
    }
}

// 生成一个随机操作符
static void gen_rand_op() {
    char ops[] = {'+', '-', '*', '/'}; // 定义操作符集合
    word_t op_index = choose(4); // 随机选择一个操作符的索引
    char op_str[2] = {ops[op_index], '\0'}; // 创建一个包含操作符的字符串
    if (strlen(buf) + strlen(op_str) < sizeof(buf)) { // 检查缓冲区是否有足够空间
        strcat(buf, op_str); // 将选中的操作符存储到缓冲区中
    }
}

// 生成随机表达式
static void gen_rand_expr(int depth) {
    if (depth > 3) { // 限制递归深度
        gen_num(); // 生成一个随机数字
        return; // 返回
    }

    switch (choose(3)) { // 随机选择生成规则
        case 0:
            gen_num(); // 生成一个随机数字
            break;
        case 1:
            strcat(buf, "("); // 添加左括号到缓冲区
            gen_rand_expr(depth + 1); // 递归生成表达式
            strcat(buf, ")"); // 添加右括号到缓冲区
            break;
        default:
            gen_rand_expr(depth + 1); // 递归生成表达式
            gen_rand_op(); // 生成一个随机操作符
            gen_rand_expr(depth + 1); // 递归生成表达式
            break;
    }
}

// 检查在buf缓冲区中是否存在除以零的情况
static int check_division_by_zero() {
    char *p = buf; // 定义一个指针指向缓冲区
    while (*p) { // 遍历缓冲区
        if (*p == '/' && (*(p + 1) == '0' || *(p + 1) == '\0' || *(p + 1) == ' ' || *(p + 1) == '(')) {
            return 1; // 表达式中存在除零行为
        }
        p++; // 指针后移
    }
    return 0; // 表达式中不存在除零行为
}

int main(int argc, char *argv[]) {
    int seed = time(0); // 获取当前时间作为随机数种子
    srand(seed); // 设置随机数种子
    int loop = 1; // 定义循环次数，默认为1
    if (argc > 1) { // 如果有命令行参数
        sscanf(argv[1], "%d", &loop); // 读取命令行参数作为循环次数
    }

    for (int i = 0; i < loop; i++) { // 循环生成表达式
        buf[0] = '\0'; // 清空缓冲区
        do {
            buf[0] = '\0'; // 清空缓冲区，重新生成表达式
            gen_rand_expr(0); // 生成随机表达式
        } while (check_division_by_zero()); // 如果存在除零情况则重新生成

        sprintf(code_buf, code_format, buf); // 将生成的表达式填充到代码格式中

        FILE *fp = fopen("/tmp/.code.c", "w"); // 打开临时文件
        assert(fp != NULL); // 断言文件成功打开
        fputs(code_buf, fp); // 将代码写入文件
        fclose(fp); // 关闭文件

        int ret = system("gcc /tmp/.code.c -o /tmp/.expr"); // 编译生成的代码
        if (ret != 0) continue; // 如果编译失败则继续

        fp = popen("/tmp/.expr", "r"); // 运行生成的可执行文件
        assert(fp != NULL); // 断言文件成功打开

        int result;
        ret = fscanf(fp, "%d", &result); // 读取运行结果
        pclose(fp); // 关闭文件

        printf("%u %s\n", result, buf); // 打印结果和表达式
    }
    return 0; // 返回0
}