`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:44:59 10/04/2017 
// Design Name: 
// Module Name:    EXMEMreg 
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
module EXMEMreg(
    input clk,
    input [47:0] pc1,
	 input [2:0] flagsMEM,
	 input [1:0] flagsWB,
	 input [5:0] opcode,
	 input [47:0] immediate,
	 input [47:0] result,
	 input [47:0] datainput,
	 input [4:0] rd,
	 output [47:0] pc1_out,
	 output [2:0] flagsMEM_out,
	 output [1:0] flagsWB_out,
	 output [5:0] opcode_out,
	 output [47:0] immediate_out,
	 output [47:0] result_out,
	 output [47:0] datainput_out,
	 output [4:0] rd_out
    );
	 
	 reg [47:0] pc1_out_reg, immediate_out_reg, result_out_reg, datainput_out_reg;
	 reg [5:0] opcode_out_reg;
	 reg [4:0] rd_out_reg;
	 reg [2:0] flagsMEM_out_reg;
	 reg [1:0] flagsWB_out_reg;	
	
	 always @ (negedge clk) begin
	 
		pc1_out_reg = pc1;
		immediate_out_reg = immediate;
		result_out_reg = result;
		opcode_out_reg = opcode;
		rd_out_reg = rd;
		flagsMEM_out_reg = flagsMEM;
		flagsWB_out_reg = flagsWB;
		datainput_out_reg = datainput;
		
	 end 
	 
	 assign pc1_out = pc1_out_reg;
	 assign flagsMEM_out = flagsMEM_out_reg;
	 assign flagsWB_out = flagsWB_out_reg;
	 assign opcode_out = opcode_out_reg;
	 assign immediate_out = immediate_out_reg;
	 assign result_out = result_out_reg;
	 assign rd_out = rd_out_reg;
	 assign datainput_out = datainput_out_reg;
	 
endmodule
