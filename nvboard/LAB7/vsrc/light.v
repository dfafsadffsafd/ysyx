module light(
    input [3:0] h,
    input [3:0] l,
    input flag,
    output reg [6:0] segh,
    output reg [6:0] segl
);

always @* begin
    if(flag) begin
    case(h)
            0: segh = 7'b0000001;  // 显示数字 0
            1: segh = 7'b1001111;  // 显示数字 1
            2: segh = 7'b0010010;  // 显示数字 2
            3: segh = 7'b0000110;  // 显示数字 3
            4: segh = 7'b1001100;  // 显示数字 4
            5: segh = 7'b0100100;  // 显示数字 5
            6: segh = 7'b0100000;  // 显示数字 6
            7: segh = 7'b0001111;  // 显示数字 7
            8: segh = 7'b0000000;  // 显示数字 8
            9: segh = 7'b0000100;  // 显示数字 9
            10: segh = 7'b0001000;  // 显示字母 A
            11: segh = 7'b1100000;  // 显示字母 B
            12: segh = 7'b0110001;  // 显示字母 C
            13: segh = 7'b1000010;  // 显示字母 D
            14: segh = 7'b0110000;  // 显示字母 E
            15: segh = 7'b0111000;  // 显示字母 F
            default: segh = 7'b1111111;  // 默认情况，全部熄灭
    endcase

        
    case(l)
            0: segl = 7'b0000001;  // 显示数字 0
            1: segl = 7'b1001111;  // 显示数字 1
            2: segl = 7'b0010010;  // 显示数字 2
            3: segl = 7'b0000110;  // 显示数字 3
            4: segl = 7'b1001100;  // 显示数字 4
            5: segl = 7'b0100100;  // 显示数字 5
            6: segl = 7'b0100000;  // 显示数字 6
            7: segl = 7'b0001111;  // 显示数字 7
            8: segl = 7'b0000000;  // 显示数字 8
            9: segl = 7'b0000100;  // 显示数字 9
            10: segl = 7'b0001000;  // 显示字母 A
            11: segl = 7'b1100000;  // 显示字母 B
            12: segl = 7'b0110001;  // 显示字母 C
            13: segl = 7'b1000010;  // 显示字母 D
            14: segl = 7'b0110000;  // 显示字母 E
            15: segl = 7'b0111000;  // 显示字母 F
            default: segl = 7'b1111111;  // 默认情况，全部熄灭    
    endcase
    
    end else begin
        segh = 7'b1111111;
        segl = 7'b1111111;
    end
end

endmodule
