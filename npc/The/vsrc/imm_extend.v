`include "/home/liu/Public/ysyx-workbench/npc/The/vsrc/defines.v"

module RISB_type(
    input  wire [4:0]       rs2,     // 输入信号：5位的源寄存器2
    input  wire [6:0]       funct7,  // 输入信号：7位的功能码（funct7）
    input  wire [`TYPE_BUS] type2,   // 输入信号：指令类型
    output reg  [11:0]      imm_12   // 输出信号：12位的立即数
);

    // 根据指令类型生成不同的立即数
    always @(*) begin
        case (type2)
            `INST_R: imm_12 = 12'b0000_0000_0000;          // R 型指令没有立即数，立即数设为 0
            `INST_I: imm_12 = {funct7, rs2};               // I 型指令，立即数由 funct7 和 rs2 组成
            // `INST_S: imm_12 = {funct7, rd};             // S 型指令（注释掉）
            // `INST_B: imm_12 = {funct7[6], rd[0], funct7[5:0], rd[4:1]}; // B 型指令（注释掉）
            default: imm_12 = 12'b0000_0000_0000;          // 默认情况下，立即数设为 0
        endcase
    end

endmodule


module Extend_12(
    input  wire [11:0]    imm_12,        // 输入信号：12位的立即数
    output wire [`RegBus] imm_12_to_32   // 输出信号：32位的符号扩展立即数
);

    // 将12位立即数符号扩展为32位
    // 使用符号扩展，即高位用imm_12[11]填充
    assign imm_12_to_32 = {{20{imm_12[11]}}, imm_12};

endmodule


/*module Extend_20(
    input  wire [19:0]    imm_20,
    output wire [`RegBus] imm_20_to_32
);
    assign imm_20_to_32 = {{12{imm_20[19]}}, imm_20};
endmodule*/


module imm_extend(
    input  wire [4:0]       rs2,       // 输入信号：5位的源寄存器2
    input  wire [6:0]       funct7,    // 输入信号：7位的功能码（funct7）
    input  wire [`TYPE_BUS] type3,     // 输入信号：指令类型
    output wire [`RegBus]   imm32      // 输出信号：32位扩展后的立即数
);

    wire [11:0] imm_12; // 中间信号：12位立即数

    // 实例化 RISB_type 模块，根据指令类型生成12位立即数
    RISB_type RISB_type_inst(
        .rs2   (rs2),        // 连接源寄存器2地址
        .funct7(funct7),     // 连接功能码
        .type2 (type3),      // 连接指令类型
        .imm_12(imm_12)      // 输出12位立即数
    );

    // 实例化 Extend_12 模块，将12位立即数扩展为32位
    Extend_12 Extend_12_inst(
        .imm_12      (imm_12),    // 输入12位立即数
        .imm_12_to_32(imm32)      // 输出32位立即数
    );

    /* 
    // 如果需要扩展20位立即数，可以启用并实例化 Extend_20 模块
    Extend_20 Extend_20_inst(
        .imm_20      (imm_20),    // 输入20位立即数
        .imm_20_to_32(imm_20_to_32) // 输出32位立即数
    ); 
    */
endmodule

