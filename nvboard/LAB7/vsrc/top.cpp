#include <verilated.h>
#include "Vkeyboard_sim.h" // 生成的仿真模型头文件

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    Vkeyboard_sim* top = new Vkeyboard_sim;

    while (!Verilated::gotFinish()) {
        top->clk = !top->clk; // Toggle clock
        top->eval(); // Evaluate the model
    }
    
    delete top;
    exit(0);
}
