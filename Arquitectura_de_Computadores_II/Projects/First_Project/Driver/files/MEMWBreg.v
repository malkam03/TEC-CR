`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:41:41 10/04/2017 
// Design Name: 
// Module Name:    MEMWBreg 
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
module MEMWBreg(
	 input clk,
	 input [1:0] flagsWB,
	 input [31:0] mem_data,
	 input [31:0] direction,
	 input [4:0] rd,
	 output [1:0] flagsWB_out,
	 output [31:0] mem_data_out,
	 output [31:0] direction_out,
	 output [4:0] rd_out
    );
	 
	 
	 reg [31:0] mem_data_out_reg, direction_out_reg;
	 reg [4:0] rd_out_reg;
	 reg [1:0] flagsWB_out_reg;
	 
	 always @ (negedge clk) begin	
		mem_data_out_reg = mem_data;
		direction_out_reg = direction;
		rd_out_reg = rd;
		flagsWB_out_reg = flagsWB;
	 end
	 
	 assign mem_data_out = mem_data_out_reg;
	 assign direction_out = direction_out_reg;
	 assign rd_out = rd_out_reg;
	 assign flagsWB_out = flagsWB_out_reg;


endmodule
