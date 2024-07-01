#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h" 
#include "stdio.h"
#include "nvboard.h"
#include <stdlib.h>
#include <time.h>

VerilatedContext* contextp = nullptr;
VerilatedVcdC* tfp = nullptr;
static Vtop* top;
static TOP_NAME dut;

void nvboard_bind_all_pins(Vtop* top);

int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  //sim_init();
  while(true){
     dut.eval();
     nvboard_update();
  }
  top->final();
  nvboard_quit();
  delete top;
  return 0;
  //sim_exit();
}
