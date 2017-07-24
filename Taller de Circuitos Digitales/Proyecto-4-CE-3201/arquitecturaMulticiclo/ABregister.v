`timescale 1ns / 1ps
module ABregister(DataIn, DataOut ,CLK);
input [31:0] DataIn;
input CLK;
output reg [31:0] DataOut;


always @(posedge CLK) begin

 DataOut <= DataIn;
 end
 endmodule 
