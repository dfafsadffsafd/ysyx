module top(
    input clk,          // 时钟信号
    input clrn,         // 复位信号，低电平有效
    input ps2_clk,      // PS/2 键盘时钟信号
    input ps2_data,     // PS/2 键盘数据信号
    output reg flag = 1, // 键盘按键有效标志
    output reg flag2 = 1, // 键盘按键第二标志
    //output VGA_CLK,
    output [6:0] seg0,   // 七段数码管显示信号 0
    output [6:0] seg1,   // 七段数码管显示信号 1
    output [6:0] segm0,  // 七段数码管显示信号 m0
    output [6:0] segm1,  // 七段数码管显示信号 m1
    output [6:0] segh0,  // 七段数码管显示信号 h0
    output [6:0] segh1   // 七段数码管显示信号 h1
);
    //assign VGA_CLK = clk;
    wire [7:0] data_asc;   // ASCII 数据
    wire [7:0] data_code;  // 键盘扫描码
    wire ready;            // 数据准备好信号
    wire overflow;         // FIFO 溢出信号

    reg [7:0] data_p;      // 用于存储上一次的键盘数据
    reg [7:0] count = 0;   // 记录按键次数

    reg all = 1;           // 控制七段数码管显示标志

    reg [6:0] count_clk = 0; // 分频计数器
    reg clk_b = 0;           // 分频时钟信号
    //读取数据的时钟频率是键盘接受模块的时钟的100倍
    always @(posedge clk) begin
        if(count_clk == 100) begin
            count_clk <= 0;
            clk_b <= ~clk_b; // 时钟信号反转
        end else
            count_clk <= count_clk + 1;
    end

    // 处理 PS/2 键盘输入信号
    reg nextdata_n2;
    ps2_keyboard S(
        .clk(clk),
        .clrn(~clrn),
        .ps2_clk(ps2_clk),
        .ps2_data(ps2_data),
        .data(data_code),
        .ready(ready),
        .nextdata_n(nextdata_n2),
        .overflow(overflow)
    );
    ram ram1(
        .code(data_code),
        .addr(data_asc)
    );
    // 将按键次数转换为七段数码管显示
    light L1(
        .h(count[7:4]),
        .l(count[3:0]),
        .flag(all),
        .segh(segh1),
        .segl(segh0)
    );

    // 将 ASCII 数据转换为七段数码管显示
    light L2(
        .h(data_asc[7:4]),
        .l(data_asc[3:0]),
        .flag(flag),
        .segh(segm1),
        .segl(segm0)
    );

    // 将上一次的键盘数据转换为七段数码管显示
    light L3(
        .h(data_p[7:4]),
        .l(data_p[3:0]),
        .flag(flag),
        .segh(seg1),
        .segl(seg0)
    );

    // 键盘数据读取
    always @(posedge clk_b) begin
        if (ready) begin
            //确保当前接收到的扫描码不是释放码 0xF0,就正常显示，flag2 为高电平，表示当前是处理按键按下的状态
            if(data_code != 8'hf0 && flag2) begin
            //if(1) begin
                //将当前的 data_code 存储在 data_p 中，表示这是一个有效的按键扫描码，并且设置 flag 和 flag2 为高电平，表示按键按下且有效。
                data_p <= data_code;              
                flag2 <= 1;
                flag <= 1;
            
            //前接收到的扫描码是释放码 0xF0，表示按键被释放。
            end else if (data_code == 8'hf0) begin
                data_p <= data_code;
                //按键计数 count，记录一次按键释放事件
                count <= count + 1;
                flag <= 0;
                flag2 <= 0;
            //如果 flag2 为低电平，表示前一个扫描码已经处理完毕，可以处理下一个扫描码
            end else if(!flag2) begin
                data_p <= data_code;
                //flag2 为高电平，表示准备处理新的按键事件，而 flag 设置为低电平，表示目前没有新的按键按下。
                flag2 <= 1;
                flag <= 0;
            end

            nextdata_n2 <= 0; // 准备读取下一个数据
        end else begin
            nextdata_n2 <= 1; // 暂停读取数据
        end
    end
endmodule
