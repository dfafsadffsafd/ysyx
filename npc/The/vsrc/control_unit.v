`include "/home/liu/Public/ysyx-workbench/npc/The/vsrc/defines.v"


module control_unit(
    input  wire [`RegBus]   inst,
    output wire [4:0]       rd_11_7,
    output wire [4:0]       rs1_19_15,
    output wire [4:0]       rs2_24_20,
    output wire [6:0]       fun7_31_25,
    output reg  [`TYPE_BUS] type1,       //inst type
    output reg              aluc,       //alu operation typp
    output reg              m1          //mux1 sel
);

    import "DPI-C" function void ebreak(input int station, input int inst);

    wire [6:0] opcode_6_0 = inst[6:0];
    wire [2:0] fun3_14_12 = inst[14:12]; 
    assign rd_11_7    = inst[11:7];
    assign rs1_19_15  = inst[19:15];
    assign rs2_24_20  = inst[24:20];
    assign fun7_31_25 = inst[31:25];  

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
