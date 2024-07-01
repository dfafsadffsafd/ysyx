module top(clk, ra);
  input clk;
  output reg [7:0] ra;

  wire feedback;
  
  // 计算反馈位，作为新的最高有效位
  assign feedback = ra[4] ^ ra[3] ^ ra[2] ^ ra[0];
  always @(posedge clk ) begin
    if (ra == 0) begin
      ra <= 8'b00000001; // 初始状态
      end else begin
        ra <= {feedback, ra[7:1]};
      end
      end
endmodule

