all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator -Wall --cc --exe --build ../verilator/Double-pole-switch/main.cpp ../verilator/Double-pole-switch/top.v 
	../verilator/Double-pole-switch/obj_dir/Vtop
include ../Makefile
