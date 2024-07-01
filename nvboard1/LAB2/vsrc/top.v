module top(a, en, f, b, s, dig);
  input [7:0] a;
  input en;
  output reg f;
  output reg [2:0] b;
  output reg s;
  output reg [6:0] dig;
  
  //f 的计算
  assign f=a[0]|a[1]|a[2]|a[3]|a[4]|a[5]|a[6]|a[7];
  always@(a or en) begin
    if(en) begin
      b=0;
      //优先编码
      casez(a)
        8'b1???????: b=3'b111;
        8'b01??????: b=3'b110;
        8'b001?????: b=3'b101;
        8'b0001????: b=3'b100;
        8'b00001???: b=3'b011;
        8'b000001??: b=3'b010;
        8'b0000001?: b=3'b001;
        8'b00000001: b=3'b000;
        default: b=3'b000;
      endcase
      //状态和 7 段显示控制
      if(f==1) begin
        s=1;
        case(b)
		3'b000: dig=7'b1000000;
		3'b001: dig=7'b1111001;
		3'b010: dig=7'b0100100;
		3'b011: dig=7'b0110000;
		3'b100: dig=7'b0011001;
		3'b101: dig=7'b0010010;
		3'b110: dig=7'b0000010;
		3'b111: dig=7'b1111000;
        endcase
      end
      else begin
        s=0;
        dig=7'b1111111;
      end
    end
    //使能信号控制
    else begin
      b=0;
      s=0;
      dig=7'b1111111;
    end
  end
endmodule
