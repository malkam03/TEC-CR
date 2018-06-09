`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:41:37 05/29/2017 
// Design Name: 
// Module Name:    Mux_Sel_PC 
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
module Mux_Sel_PC(
    input [47:0] output_ALU,
    input [47:0] output_PC1,
    input sel_pc,
    output [47:0] output_sel_pc
    );
	
	
	assign output_sel_pc = (sel_pc) ? output_ALU : output_PC1;
	
endmodule
