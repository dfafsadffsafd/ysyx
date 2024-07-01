#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->A, 4, SW0, SW1, SW2, SW3);
	nvboard_bind_pin( &top->b, 4, SW4, SW5, SW6, SW7);
	nvboard_bind_pin( &top->option, 4, BTNU, BTNL, BTNC, BTNR);
	nvboard_bind_pin( &top->carry, 1, LD0);
	nvboard_bind_pin( &top->overflow, 1, LD1);
	nvboard_bind_pin( &top->zero, 1, LD2);
	nvboard_bind_pin( &top->result, 4, LD3, LD4, LD5, LD6);
}
