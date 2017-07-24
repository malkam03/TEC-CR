`timescale 1ns / 1ps
module RegFile(RA,RB,W,WE,WD,RDA,RDB,CLK);
input [4:0] RA, RB, W;
input [31:0] WD;
input WE, CLK;
output [31:0] RDA, RDB;
reg [31:0] RegFile [31:0];
reg [5:0] i;

always @(posedge CLK)
 if(WE) RegFile[W] <= WD;


assign RDA = RegFile[RA];
assign RDB = RegFile[RB];

initial begin
for (i = 0; i < 32; i = i + 1)
 RegFile[i] = 32'd0;
end
endmodule 
