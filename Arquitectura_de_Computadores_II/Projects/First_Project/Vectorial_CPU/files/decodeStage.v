`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:15:08 10/04/2017 
// Design Name: 
// Module Name:    decodeStage 
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
module decodeStage(
    input clk,
    input rst,
	 input [47:0] pc1,
    input [5:0] opcode,
    input [4:0] rs,
    input [4:0] rd,
	 input [31:0] data_input, //WB
	 input reg_wr, //WB
    input [31:0] immediate,
	 input flagsDECO,
    input [3:0] flagsALU,
    input [2:0] flagsMEM,
    input [1:0] flagsWB,
	 output [3:0] flagsALU_out,
    output [2:0] flagsMEM_out,
    output [1:0] flagsWB_out,
    output [31:0] dataOne,
    output [31:0] dataTwo,
	 output [31:0] immediate_out
    );

	 BancoRegistros banReg(
		.clk(),
		.dir_a(rs),
		.dir_b(rd),
		.dir_wra(rd),
		.di(data_input),
		.reg_rd(flagsDECO),
		.reg_wr(reg_wr),
		.doa(dataOne),
		.dob(dataTwo)
	 );
	 
	 assign flagsALU_out = flagsALU;
	 assign flagsMEM_out = flagsMEM;
	 assign flagsWB_out = flagsWB;
	 assign immediate_out = immediate;
	 
endmodule
