#include "verilated.h"
#include "Vtop.h"
#include "stdio.h"
#include <nvboard.h>
#include <stdlib.h>
#include <time.h>

static TOP_NAME dut;
Vtop *top;//module object

void nvboard_bind_all_pins(Vtop* top);

static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}

static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}

int main(int argc, char** argv){
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  top = new Vtop;
  
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  reset(10);

  while(1) {
    nvboard_update();
    single_cycle();
  }
  
   top->final();
   delete top;
   nvboard_quit();
   return 0;
}

