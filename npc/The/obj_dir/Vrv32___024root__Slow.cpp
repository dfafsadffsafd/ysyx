// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vrv32.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vrv32__Syms.h"
#include "Vrv32___024root.h"

void Vrv32___024root___ctor_var_reset(Vrv32___024root* vlSelf);

Vrv32___024root::Vrv32___024root(Vrv32__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vrv32___024root___ctor_var_reset(this);
}

void Vrv32___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vrv32___024root::~Vrv32___024root() {
}
