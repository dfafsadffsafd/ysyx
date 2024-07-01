`include "/home/liu/Public/ysyx-workbench/npc/The/vsrc/defines.v"


module control_unit(
    input  wire [`RegBus]   inst,        // 输入信号：指令
    output wire [4:0]       rd_11_7,     // 输出信号：目的寄存器地址
    output wire [4:0]       rs1_19_15,   // 输出信号：源寄存器1地址
    output wire [4:0]       rs2_24_20,   // 输出信号：源寄存器2地址
    output wire [6:0]       fun7_31_25,  // 输出信号：功能码
    output reg  [`TYPE_BUS] type1,       // 输出信号：指令类型
    output reg              aluc,        // 输出信号：ALU 操作类型
    output reg              m1           // 输出信号：多路复用器选择信号
);


    import "DPI-C" function void ebreak(input int station, input int inst);//处理 EBREAK 指令

    wire [6:0] opcode_6_0 = inst[6:0];      // 指令的操作码
    wire [2:0] fun3_14_12 = inst[14:12];    // 指令的功能码
    assign rd_11_7    = inst[11:7];         // 目的寄存器地址
    assign rs1_19_15  = inst[19:15];        // 源寄存器1地址
    assign rs2_24_20  = inst[24:20];        // 源寄存器2地址
    assign fun7_31_25 = inst[31:25];        // 功能码

    always @(*) begin
        case(opcode_6_0)
            `INST_TYPE_I: begin
                type1 = `INST_I;   m1   = `MUX1_imm;
                case (fun3_14_12)
                    `INST_ADDI: aluc = `ADD;
                    default:    aluc = `ADD;  //uae
                endcase
            end
            `INST_TYPE_E: begin
                case ({fun7_31_25, rs2_24_20})
                    `INST_EBREAK: ebreak(`HIT_GOOD_TRAP, inst);
                     default:     ebreak(`ABORT, inst);
                endcase
            end
            default: begin   //uae
                type1 = 3'd0;
                aluc  = `ADD;
                m1    = `MUX1_imm;
            end
        endcase
    end

endmodule
