`timescale 1ns / 1ps
module DataMemory(Clk, Address, WriteData, MemWrite, MemRead, MemData);
input [31:0] Address, WriteData;
input MemRead, MemWrite, Clk;
output [31:0] MemData;
wire [31:0] MemData;
reg [31:0] RegFile [512:0];

always @ (posedge Clk) begin
 if(MemWrite==1'b1)begin
 RegFile[Address] <= WriteData;
 end
 end
 assign MemData = (MemRead==1'b1)? RegFile[Address] : 0;
initial begin //load in data and instructions of program
 RegFile[0] <= 32'd8;
 RegFile[1] <= 32'd1;
 RegFile[2] <= 32'd1;

 RegFile[128] <= 32'h8c030000;
 RegFile[132] <= 32'h8c040001;
 RegFile[136] <= 32'h8c050002;
 RegFile[140] <=32'h8c010002;
 RegFile[144] <=32'h10600004;
 RegFile[148] <=32'h00852020;
 RegFile[152] <=32'h00852822;
 RegFile[156] <=32'h00611820;
 RegFile[160] <=32'h1000fffb;
 RegFile[164] <=32'hac040006;

 end
endmodule 
