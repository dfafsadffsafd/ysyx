`include "/home/liu/Public/ysyx-workbench/npc/The/vsrc/defines.v"


module register_file(
    input  wire           clk,        // 时钟信号
    input  wire           rst,        // 复位信号
    input  wire           clk1_flag,  // 时钟标志信号，用于控制写入操作
    input  wire [4:0]     rs1,        // 源寄存器1地址
    input  wire [4:0]     rs2,        // 源寄存器2地址
    input  wire [4:0]     rd,         // 目标寄存器地址
    input  wire [`RegBus] result,     // 要写入的结果数据
    output wire [`RegBus] src1,       // 源寄存器1数据输出
    output wire [`RegBus] src2        // 源寄存器2数据输出
);


    integer i;
    reg[`RegBus] regs[`RegNum-1 : 0]; // 定义寄存器数组，存储32个32位寄存器
    wire wen; // 写使能信号

    assign wen = (clk1_flag == 1'b1);

    //wire register
    always @(posedge clk) begin
        if(rst == `RST_VAL) begin
            for(i=0; i<32; i=i+1) begin
                regs[i] <= `RegRstVal;// 复位时，将所有寄存器重置为默认值  
            end
        end else if((wen == 1'b1) && (rd != `Reg0))
            regs[rd] <= result; // 当写使能信号有效且目标寄存器地址不为0时，写入数据
        else
            regs[rd] <= regs[rd]; 
    end

    //read register
    //读取源寄存器 rs1 和 rs2 的值。如果源寄存器地址为0，则返回寄存器0的默认值 Reg0_VAL，否则返回寄存器数组中的相应值。
    assign src1 = (rs1 == `Reg0) ? `Reg0_VAL : regs[rs1];
    assign src2 = (rs2 == `Reg0) ? `Reg0_VAL : regs[rs2];
   
endmodule
