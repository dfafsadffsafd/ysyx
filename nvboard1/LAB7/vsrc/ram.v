module ram (
    input [7:0] code,   // 输入的8位编码
    output reg [7:0] addr // 输出的8位地址
);
    reg [7:0] ram [255:0]; // 声明一个256字节的RAM存储器

    // 初始化存储器，从指定的文件中读取数据
    initial begin
        $readmemh("/home/liu/Public/ysyx-workbench/nvboard/LAB7/resource/memoo.txt", ram, 0, 255);
    end

    // 每次输入改变时更新输出地址
    always @(*) begin
        addr = ram[code]; // 将RAM中对应code的值赋给addr
    end
endmodule
