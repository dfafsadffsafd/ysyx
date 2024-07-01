#include <nvboard.h>
#include <Vtop.h>
#include "verilated_vcd_c.h"
#include "stdio.h"
#include <stdlib.h>
#include <time.h>

static TOP_NAME dut;
Vtop *top;

void nvboard_bind_all_pins(Vtop* top);

/*
static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}

static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}
*/

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);
  
  nvboard_bind_all_pins(&dut);
  nvboard_init();

   int a,b;
   top = new Vtop;
    
   while(1){
       dut.eval();
       nvboard_update();
   }
   top->final();
   delete top;
   nvboard_quit();
   return 0;
}

