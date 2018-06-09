`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:21:14 05/30/2017 
// Design Name: 
// Module Name:    RegPC 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module RegPC(
	input [47:0] pc_in,
	input clk,
	input rst,
	output [47:0] pc_out
   );
	
	reg [47:0] pc_reg;
	
	/*initial begin
		pc_reg = 48'b0;
	end*/
	
	always @ (negedge clk) begin
		if(rst) pc_reg = 48'b0;
		pc_reg = pc_in;
	end
	 
	assign pc_out = pc_reg;
	
endmodule
