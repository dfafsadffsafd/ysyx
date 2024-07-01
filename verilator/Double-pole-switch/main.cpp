#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated.h"

int main(int argc, char** argv){
	Verilated::commandArgs(argc, argv);
	Vtop* top = new Vtop;

	while (!Verilated::gotFinish()) {
		        int a = rand() & 1; 
			int b = rand() & 1;
			top->a = a;          // 将随机值赋给顶层模块的输入a
			top->b = b;          // 将随机值赋给顶层模块的输入b

			top->eval();         // 计算顶层模块

			 printf("a = %d, b = %d, f = %d\n", a, b, top->f);
			 assert(top->f == (a ^ b));  // 验证顶层模块的输出是否正确
			}
			delete top;  // 清理分配的内存
			    return 0;
}
