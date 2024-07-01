// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vrv32__Syms.h"


VL_ATTR_COLD void Vrv32___024root__trace_init_sub__TOP__0(Vrv32___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vrv32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+59,"clk", false,-1);
    tracep->declBit(c+60,"rst", false,-1);
    tracep->declBus(c+61,"inst", false,-1, 31,0);
    tracep->declBus(c+62,"pc", false,-1, 31,0);
    tracep->pushNamePrefix("rv32 ");
    tracep->declBit(c+59,"clk", false,-1);
    tracep->declBit(c+60,"rst", false,-1);
    tracep->declBus(c+61,"inst", false,-1, 31,0);
    tracep->declBus(c+62,"pc", false,-1, 31,0);
    tracep->declBit(c+23,"clk1_flag", false,-1);
    tracep->declBit(c+24,"clk2_flag", false,-1);
    tracep->declBus(c+63,"rs1", false,-1, 4,0);
    tracep->declBus(c+64,"rs2", false,-1, 4,0);
    tracep->declBus(c+65,"rd", false,-1, 4,0);
    tracep->declBus(c+66,"funct7", false,-1, 6,0);
    tracep->declBus(c+3,"type4", false,-1, 2,0);
    tracep->declBit(c+4,"m1", false,-1);
    tracep->declBus(c+5,"aluc", false,-1, 0,0);
    tracep->declBus(c+9,"result", false,-1, 31,0);
    tracep->declBus(c+10,"src1", false,-1, 31,0);
    tracep->declBus(c+11,"src2", false,-1, 31,0);
    tracep->declBus(c+6,"imm", false,-1, 31,0);
    tracep->declBus(c+10,"num1", false,-1, 31,0);
    tracep->declBus(c+12,"num2", false,-1, 31,0);
    tracep->pushNamePrefix("PC_inst ");
    tracep->declBit(c+59,"clk", false,-1);
    tracep->declBit(c+60,"rst", false,-1);
    tracep->declBit(c+24,"clk2_flag", false,-1);
    tracep->declBus(c+62,"pc", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("alu_inst ");
    tracep->declBit(c+5,"aluc", false,-1);
    tracep->declBus(c+10,"num1", false,-1, 31,0);
    tracep->declBus(c+12,"num2", false,-1, 31,0);
    tracep->declBus(c+9,"result", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("clk_count_inst ");
    tracep->declBit(c+59,"clk", false,-1);
    tracep->declBit(c+60,"rst", false,-1);
    tracep->declBit(c+23,"clk1_flag", false,-1);
    tracep->declBit(c+24,"clk2_flag", false,-1);
    tracep->declBus(c+25,"clk_cnt", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("control_unit_inst ");
    tracep->declBus(c+61,"inst", false,-1, 31,0);
    tracep->declBus(c+65,"rd_11_7", false,-1, 4,0);
    tracep->declBus(c+63,"rs1_19_15", false,-1, 4,0);
    tracep->declBus(c+64,"rs2_24_20", false,-1, 4,0);
    tracep->declBus(c+66,"fun7_31_25", false,-1, 6,0);
    tracep->declBus(c+3,"type1", false,-1, 2,0);
    tracep->declBit(c+5,"aluc", false,-1);
    tracep->declBit(c+4,"m1", false,-1);
    tracep->declBus(c+67,"opcode_6_0", false,-1, 6,0);
    tracep->declBus(c+68,"fun3_14_12", false,-1, 2,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("i1 ");
    tracep->declBus(c+69,"NR_KEY", false,-1, 31,0);
    tracep->declBus(c+70,"KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+71,"DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+12,"out", false,-1, 31,0);
    tracep->declBus(c+4,"key", false,-1, 0,0);
    tracep->declArray(c+13,"lut", false,-1, 65,0);
    tracep->pushNamePrefix("i0 ");
    tracep->declBus(c+69,"NR_KEY", false,-1, 31,0);
    tracep->declBus(c+70,"KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+71,"DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+72,"HAS_DEFAULT", false,-1, 31,0);
    tracep->declBus(c+12,"out", false,-1, 31,0);
    tracep->declBus(c+4,"key", false,-1, 0,0);
    tracep->declBus(c+73,"default_out", false,-1, 31,0);
    tracep->declArray(c+13,"lut", false,-1, 65,0);
    tracep->declBus(c+74,"PAIR_LEN", false,-1, 31,0);
    for (int i = 0; i < 2; ++i) {
        tracep->declQuad(c+16+i*2,"pair_list", true,(i+0), 32,0);
    }
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+1+i*1,"key_list", true,(i+0), 0,0);
    }
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+20+i*1,"data_list", true,(i+0), 31,0);
    }
    tracep->declBus(c+22,"lut_out", false,-1, 31,0);
    tracep->declBit(c+7,"hit", false,-1);
    tracep->declBus(c+75,"i", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("imm_extend_inst ");
    tracep->declBus(c+64,"rs2", false,-1, 4,0);
    tracep->declBus(c+66,"funct7", false,-1, 6,0);
    tracep->declBus(c+3,"type3", false,-1, 2,0);
    tracep->declBus(c+6,"imm32", false,-1, 31,0);
    tracep->declBus(c+8,"imm_12", false,-1, 11,0);
    tracep->pushNamePrefix("Extend_12_inst ");
    tracep->declBus(c+8,"imm_12", false,-1, 11,0);
    tracep->declBus(c+6,"imm_12_to_32", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("RISB_type_inst ");
    tracep->declBus(c+64,"rs2", false,-1, 4,0);
    tracep->declBus(c+66,"funct7", false,-1, 6,0);
    tracep->declBus(c+3,"type2", false,-1, 2,0);
    tracep->declBus(c+8,"imm_12", false,-1, 11,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("register_file_inst ");
    tracep->declBit(c+59,"clk", false,-1);
    tracep->declBit(c+60,"rst", false,-1);
    tracep->declBit(c+23,"clk1_flag", false,-1);
    tracep->declBus(c+63,"rs1", false,-1, 4,0);
    tracep->declBus(c+64,"rs2", false,-1, 4,0);
    tracep->declBus(c+65,"rd", false,-1, 4,0);
    tracep->declBus(c+9,"result", false,-1, 31,0);
    tracep->declBus(c+10,"src1", false,-1, 31,0);
    tracep->declBus(c+11,"src2", false,-1, 31,0);
    tracep->declBus(c+26,"i", false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+27+i*1,"regs", true,(i+0), 31,0);
    }
    tracep->declBit(c+23,"wen", false,-1);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vrv32___024root__trace_init_top(Vrv32___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vrv32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32___024root__trace_init_top\n"); );
    // Body
    Vrv32___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vrv32___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vrv32___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vrv32___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vrv32___024root__trace_register(Vrv32___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vrv32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vrv32___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vrv32___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vrv32___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vrv32___024root__trace_full_sub_0(Vrv32___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vrv32___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32___024root__trace_full_top_0\n"); );
    // Init
    Vrv32___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vrv32___024root*>(voidSelf);
    Vrv32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vrv32___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vrv32___024root__trace_full_sub_0(Vrv32___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vrv32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vrv32___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    VlWide<3>/*95:0*/ __Vtemp_h03a154e0__0;
    // Body
    bufp->fullBit(oldp+1,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__key_list[0]));
    bufp->fullBit(oldp+2,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__key_list[1]));
    bufp->fullCData(oldp+3,(vlSelf->rv32__DOT__type4),3);
    bufp->fullBit(oldp+4,(vlSelf->rv32__DOT__m1));
    bufp->fullBit(oldp+5,(vlSelf->rv32__DOT__aluc));
    bufp->fullIData(oldp+6,(vlSelf->rv32__DOT__imm),32);
    bufp->fullBit(oldp+7,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__hit));
    bufp->fullSData(oldp+8,(vlSelf->rv32__DOT__imm_extend_inst__DOT__imm_12),12);
    bufp->fullIData(oldp+9,(((IData)(vlSelf->rv32__DOT__aluc)
                              ? (vlSelf->rv32__DOT__src1 
                                 + vlSelf->rv32__DOT__num2)
                              : (vlSelf->rv32__DOT__src1 
                                 + vlSelf->rv32__DOT__num2))),32);
    bufp->fullIData(oldp+10,(vlSelf->rv32__DOT__src1),32);
    bufp->fullIData(oldp+11,(vlSelf->rv32__DOT__src2),32);
    bufp->fullIData(oldp+12,(vlSelf->rv32__DOT__num2),32);
    __Vtemp_h03a154e0__0[0U] = (IData)((0x100000000ULL 
                                        | (QData)((IData)(vlSelf->rv32__DOT__imm))));
    __Vtemp_h03a154e0__0[1U] = ((vlSelf->rv32__DOT__src2 
                                 << 1U) | (IData)((
                                                   (0x100000000ULL 
                                                    | (QData)((IData)(vlSelf->rv32__DOT__imm))) 
                                                   >> 0x20U)));
    __Vtemp_h03a154e0__0[2U] = (vlSelf->rv32__DOT__src2 
                                >> 0x1fU);
    bufp->fullWData(oldp+13,(__Vtemp_h03a154e0__0),66);
    bufp->fullQData(oldp+16,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__pair_list[0]),33);
    bufp->fullQData(oldp+18,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__pair_list[1]),33);
    bufp->fullIData(oldp+20,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__data_list[0]),32);
    bufp->fullIData(oldp+21,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__data_list[1]),32);
    bufp->fullIData(oldp+22,(vlSelf->rv32__DOT__i1__DOT__i0__DOT__lut_out),32);
    bufp->fullBit(oldp+23,((1U == (IData)(vlSelf->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
    bufp->fullBit(oldp+24,((2U == (IData)(vlSelf->rv32__DOT__clk_count_inst__DOT__clk_cnt))));
    bufp->fullCData(oldp+25,(vlSelf->rv32__DOT__clk_count_inst__DOT__clk_cnt),2);
    bufp->fullIData(oldp+26,(vlSelf->rv32__DOT__register_file_inst__DOT__i),32);
    bufp->fullIData(oldp+27,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[0]),32);
    bufp->fullIData(oldp+28,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[1]),32);
    bufp->fullIData(oldp+29,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[2]),32);
    bufp->fullIData(oldp+30,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[3]),32);
    bufp->fullIData(oldp+31,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[4]),32);
    bufp->fullIData(oldp+32,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[5]),32);
    bufp->fullIData(oldp+33,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[6]),32);
    bufp->fullIData(oldp+34,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[7]),32);
    bufp->fullIData(oldp+35,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[8]),32);
    bufp->fullIData(oldp+36,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[9]),32);
    bufp->fullIData(oldp+37,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[10]),32);
    bufp->fullIData(oldp+38,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[11]),32);
    bufp->fullIData(oldp+39,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[12]),32);
    bufp->fullIData(oldp+40,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[13]),32);
    bufp->fullIData(oldp+41,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[14]),32);
    bufp->fullIData(oldp+42,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[15]),32);
    bufp->fullIData(oldp+43,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[16]),32);
    bufp->fullIData(oldp+44,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[17]),32);
    bufp->fullIData(oldp+45,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[18]),32);
    bufp->fullIData(oldp+46,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[19]),32);
    bufp->fullIData(oldp+47,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[20]),32);
    bufp->fullIData(oldp+48,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[21]),32);
    bufp->fullIData(oldp+49,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[22]),32);
    bufp->fullIData(oldp+50,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[23]),32);
    bufp->fullIData(oldp+51,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[24]),32);
    bufp->fullIData(oldp+52,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[25]),32);
    bufp->fullIData(oldp+53,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[26]),32);
    bufp->fullIData(oldp+54,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[27]),32);
    bufp->fullIData(oldp+55,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[28]),32);
    bufp->fullIData(oldp+56,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[29]),32);
    bufp->fullIData(oldp+57,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[30]),32);
    bufp->fullIData(oldp+58,(vlSelf->rv32__DOT__register_file_inst__DOT__regs[31]),32);
    bufp->fullBit(oldp+59,(vlSelf->clk));
    bufp->fullBit(oldp+60,(vlSelf->rst));
    bufp->fullIData(oldp+61,(vlSelf->inst),32);
    bufp->fullIData(oldp+62,(vlSelf->pc),32);
    bufp->fullCData(oldp+63,((0x1fU & (vlSelf->inst 
                                       >> 0xfU))),5);
    bufp->fullCData(oldp+64,((0x1fU & (vlSelf->inst 
                                       >> 0x14U))),5);
    bufp->fullCData(oldp+65,((0x1fU & (vlSelf->inst 
                                       >> 7U))),5);
    bufp->fullCData(oldp+66,((vlSelf->inst >> 0x19U)),7);
    bufp->fullCData(oldp+67,((0x7fU & vlSelf->inst)),7);
    bufp->fullCData(oldp+68,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->fullIData(oldp+69,(2U),32);
    bufp->fullIData(oldp+70,(1U),32);
    bufp->fullIData(oldp+71,(0x20U),32);
    bufp->fullIData(oldp+72,(0U),32);
    bufp->fullIData(oldp+73,(0U),32);
    bufp->fullIData(oldp+74,(0x21U),32);
    bufp->fullIData(oldp+75,(2U),32);
}
