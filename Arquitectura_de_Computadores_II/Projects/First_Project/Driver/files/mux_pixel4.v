`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:52:24 03/17/2018 
// Design Name: 
// Module Name:    mux_pixel4 
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
module mux_pixel4(
    input [7:0] pixel,
    input [31:0] immediate,
    input select_pixel4,
    output [7:0] mux_pixel_out
    );
	 
	assign mux_pixel_out = (select_pixel4) ? immediate[7:0] : pixel;


endmodule
