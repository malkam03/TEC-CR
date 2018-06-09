`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:55:31 05/29/2017 
// Design Name: 
// Module Name:    Mux_Sel_Dat 
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
module Mux_Sel_Dat(
    input [31:0] mem_data,
    input [31:0] calc,
    input sel_dat,
    output [31:0] output_Y
    );
	 
	 assign output_Y = (sel_dat) ? calc : mem_data;

endmodule
