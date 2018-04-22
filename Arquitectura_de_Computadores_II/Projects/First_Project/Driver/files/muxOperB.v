`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:05:10 03/16/2018 
// Design Name: 
// Module Name:    muxOperB 
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
module muxOperB(
    input [31:0] datB,
    input [31:0] immediate,
    input sel_operB,
    output [31:0] output_B
    );
	 
	 assign output_B = (sel_operB) ? immediate : datB;


endmodule
