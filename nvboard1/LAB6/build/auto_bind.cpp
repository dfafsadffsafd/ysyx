#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->clk, 1, BTNU);
	nvboard_bind_pin( &top->ra, 8, LD7, LD6, LD5, LD4, LD3, LD2, LD1, LD0);
}
