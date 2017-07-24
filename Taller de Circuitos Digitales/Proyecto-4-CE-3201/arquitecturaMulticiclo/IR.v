`timescale 1ns / 1ps
module IR(IRWrite, DataIn, DataOut ,CLK);
input [31:0] DataIn;
input CLK, IRWrite;
output [31:0] DataOut;
reg [31:0] DataOut;

always @(posedge CLK) begin
 if(IRWrite==1'b1) begin
 DataOut <= DataIn;
 end
 end
endmodule 
