`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:43:50 03/17/2018 
// Design Name: 
// Module Name:    mux_alu_concat 
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
module mux_alu_concat(
    input [31:0] alu,
    input [31:0] concat,
	 input mux_sel,
    output [31:0] mux_out
    );

	 assign mux_out = (mux_sel) ? concat : alu;

endmodule
