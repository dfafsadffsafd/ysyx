// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vrv32.h for the primary calling header

#ifndef VERILATED_VRV32___024ROOT_H_
#define VERILATED_VRV32___024ROOT_H_  // guard

#include "verilated.h"

class Vrv32__Syms;

class Vrv32___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*2:0*/ rv32__DOT__type4;
    CData/*0:0*/ rv32__DOT__m1;
    CData/*0:0*/ rv32__DOT__aluc;
    CData/*1:0*/ rv32__DOT__clk_count_inst__DOT__clk_cnt;
    CData/*0:0*/ rv32__DOT__i1__DOT__i0__DOT__hit;
    CData/*0:0*/ __Vtrigrprev__TOP__clk;
    CData/*0:0*/ __VactContinue;
    SData/*11:0*/ rv32__DOT__imm_extend_inst__DOT__imm_12;
    VL_IN(inst,31,0);
    VL_OUT(pc,31,0);
    IData/*31:0*/ rv32__DOT__src1;
    IData/*31:0*/ rv32__DOT__src2;
    IData/*31:0*/ rv32__DOT__imm;
    IData/*31:0*/ rv32__DOT__num2;
    IData/*31:0*/ rv32__DOT__register_file_inst__DOT__i;
    IData/*31:0*/ rv32__DOT__i1__DOT__i0__DOT__lut_out;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<IData/*31:0*/, 32> rv32__DOT__register_file_inst__DOT__regs;
    VlUnpacked<QData/*32:0*/, 2> rv32__DOT__i1__DOT__i0__DOT__pair_list;
    VlUnpacked<CData/*0:0*/, 2> rv32__DOT__i1__DOT__i0__DOT__key_list;
    VlUnpacked<IData/*31:0*/, 2> rv32__DOT__i1__DOT__i0__DOT__data_list;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vrv32__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vrv32___024root(Vrv32__Syms* symsp, const char* v__name);
    ~Vrv32___024root();
    VL_UNCOPYABLE(Vrv32___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
