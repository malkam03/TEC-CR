`timescale 1ns / 1ps
module ALUOut(DataIn, DataOut ,CLK);
input [31:0] DataIn;
input CLK;
output [31:0] DataOut;
reg [31:0] DataOut;

always @(posedge CLK) begin

 DataOut <= DataIn;
end
 endmodule 