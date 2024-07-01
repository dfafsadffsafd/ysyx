// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    // Body
    Vtop___024root___eval_static__TOP(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->flag = 1U;
    vlSelf->flag2 = 1U;
    vlSelf->top__DOT__count = 0U;
    vlSelf->top__DOT__count_clk = 0U;
    vlSelf->top__DOT__clk_b = 0U;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
    vlSelf->__Vtrigrprev__TOP__top__DOT__clk_b = vlSelf->top__DOT__clk_b;
}

extern const VlWide<16>/*511:0*/ Vtop__ConstPool__CONST_h930a4b0c_0;

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    VL_READMEM_N(true, 8, 256, 0, VL_CVT_PACK_STR_NW(16, Vtop__ConstPool__CONST_h930a4b0c_0)
                 ,  &(vlSelf->top__DOT__ram1__DOT__ram)
                 , 0U, 0xffU);
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vtop___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("/home/liu/Public/ysyx-workbench/nvboard/LAB7/vsrc/top.v", 1, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vtop___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

extern const VlUnpacked<CData/*6:0*/, 512> Vtop__ConstPool__TABLE_hdb1b10aa_0;
extern const VlUnpacked<CData/*6:0*/, 512> Vtop__ConstPool__TABLE_h074d707f_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    // Init
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    SData/*8:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    SData/*8:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    // Body
    __Vtableidx1 = (1U | ((0x1e0U & ((IData)(vlSelf->top__DOT__count) 
                                     << 5U)) | (0x1eU 
                                                & ((IData)(vlSelf->top__DOT__count) 
                                                   >> 3U))));
    vlSelf->segh1 = Vtop__ConstPool__TABLE_hdb1b10aa_0
        [__Vtableidx1];
    vlSelf->segh0 = Vtop__ConstPool__TABLE_h074d707f_0
        [__Vtableidx1];
    __Vtableidx3 = ((0x1e0U & ((IData)(vlSelf->top__DOT__data_p) 
                               << 5U)) | ((0x1eU & 
                                           ((IData)(vlSelf->top__DOT__data_p) 
                                            >> 3U)) 
                                          | (IData)(vlSelf->flag)));
    vlSelf->seg1 = Vtop__ConstPool__TABLE_hdb1b10aa_0
        [__Vtableidx3];
    vlSelf->seg0 = Vtop__ConstPool__TABLE_h074d707f_0
        [__Vtableidx3];
    vlSelf->top__DOT__data_code = vlSelf->top__DOT__S__DOT__fifo
        [vlSelf->top__DOT__S__DOT__r_ptr];
    vlSelf->top__DOT__data_asc = vlSelf->top__DOT__ram1__DOT__ram
        [vlSelf->top__DOT__data_code];
    __Vtableidx2 = ((0x1e0U & ((IData)(vlSelf->top__DOT__data_asc) 
                               << 5U)) | ((0x1eU & 
                                           ((IData)(vlSelf->top__DOT__data_asc) 
                                            >> 3U)) 
                                          | (IData)(vlSelf->flag)));
    vlSelf->segm1 = Vtop__ConstPool__TABLE_hdb1b10aa_0
        [__Vtableidx2];
    vlSelf->segm0 = Vtop__ConstPool__TABLE_h074d707f_0
        [__Vtableidx2];
}

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if (vlSelf->__VactTriggered.at(1U)) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge top.clk_b)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge top.clk_b)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->clrn = 0;
    vlSelf->ps2_clk = 0;
    vlSelf->ps2_data = 0;
    vlSelf->flag = 0;
    vlSelf->flag2 = 0;
    vlSelf->seg0 = 0;
    vlSelf->seg1 = 0;
    vlSelf->segm0 = 0;
    vlSelf->segm1 = 0;
    vlSelf->segh0 = 0;
    vlSelf->segh1 = 0;
    vlSelf->top__DOT__data_asc = 0;
    vlSelf->top__DOT__data_code = 0;
    vlSelf->top__DOT__ready = 0;
    vlSelf->top__DOT__overflow = 0;
    vlSelf->top__DOT__data_p = 0;
    vlSelf->top__DOT__count = 0;
    vlSelf->top__DOT__count_clk = 0;
    vlSelf->top__DOT__clk_b = 0;
    vlSelf->top__DOT__nextdata_n2 = 0;
    vlSelf->top__DOT__S__DOT__buffer = 0;
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->top__DOT__S__DOT__fifo[__Vi0] = 0;
    }
    vlSelf->top__DOT__S__DOT__w_ptr = 0;
    vlSelf->top__DOT__S__DOT__r_ptr = 0;
    vlSelf->top__DOT__S__DOT__count = 0;
    vlSelf->top__DOT__S__DOT__ps2_clk_sync = 0;
    vlSelf->top__DOT__S__DOT____Vlvbound_h1a91ade8__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->top__DOT__ram1__DOT__ram[__Vi0] = 0;
    }
    vlSelf->__Vdly__top__DOT__ready = 0;
    vlSelf->__Vtrigrprev__TOP__clk = 0;
    vlSelf->__Vtrigrprev__TOP__top__DOT__clk_b = 0;
}
