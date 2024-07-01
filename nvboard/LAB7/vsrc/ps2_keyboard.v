module ps2_keyboard(
    input clk,            // 时钟信号
    input clrn,           // 复位信号，低电平有效
    input ps2_clk,        // PS2 时钟信号
    input ps2_data,       // PS2 数据信号
    input nextdata_n,     // 读取下一个数据的信号，低电平有效
    output [7:0] data,    // 输出的数据
    output reg ready,     // 数据准备好信号
    output reg overflow   // FIFO 溢出信号
);
    // 内部信号，用于测试
    reg [9:0] buffer;     // PS2 数据位缓冲区
    reg [7:0] fifo[7:0];  // 数据 FIFO
    reg [2:0] w_ptr, r_ptr; // FIFO 写和读指针
    reg [3:0] count;      // PS2 数据位计数器,跟踪当前接收到的位数。
    reg [2:0] ps2_clk_sync; // 用于检测 ps2_clk 的下降沿

    // 检测 ps2_clk 的下降沿
    always @(posedge clk) begin
        ps2_clk_sync <= {ps2_clk_sync[1:0], ps2_clk};
    end

    // 采样信号，当检测到 ps2_clk 的下降沿时有效
    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

    // 主逻辑
    always @(posedge clk) begin
        if (clrn == 0) begin // 复位
            count <= 0; 
            w_ptr <= 0; 
            r_ptr <= 0;
            overflow <= 0; 
            ready <= 0;
            //$display("receive %x", buffer[8:1]);

        //数据接收和处理
        end else if (sampling) begin // 检测到 ps2_clk 的下降沿
            //$display("receive %x", buffer[8:1]);
            if (count == 4'd10) begin // 收集到完整的一个字节（10 位）
                if ((buffer[0] == 0) &&    // 起始位
                    (ps2_data) &&          // 停止位
                    (^buffer[9:1])) begin  // 奇校验
                    fifo[w_ptr] <= buffer[8:1]; // 存储键盘扫描码
                    //$display("receive %x", buffer[8:1]);
                    w_ptr <= w_ptr + 3'b1;  // 写指针增加
                    ready <= 1'b1;          // 数据准备好
                    overflow <= overflow | (r_ptr == (w_ptr + 3'b1)); // 检查 FIFO 是否溢出
                end
                count <= 0; // 准备收集下一个字节
            end else begin
                //从 ps2_data 线上接收到的数据位存储在 buffer 缓冲区的对应位置
                buffer[count] <= ps2_data; 
                count <= count + 3'b1;     // 计数器增加1000000
                //$display("receive %x", buffer[8:1]);
            end
        end

        if (ready) begin // 表示 FIFO 中有数据可以读取
            if (nextdata_n == 1'b0) begin // 备读取下一个数据
                r_ptr <= r_ptr + 3'b1;    // 读指针增加
                if (w_ptr == (r_ptr + 1'b1)) // FIFO 为空
                    ready <= 1'b0;
            end
        end
    end

    assign data = fifo[r_ptr]; // 始终输出 FIFO 中的数据

endmodule
