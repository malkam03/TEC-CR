`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:46:12 03/17/2018 
// Design Name: 
// Module Name:    mux_pixel2 
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
module mux_pixel2(
    input [7:0] pixel,
    input [31:0] immediate,
    input select_pixel2,
    output [7:0] mux_pixel_out
    );
	 
	assign mux_pixel_out = (select_pixel2) ? immediate[7:0] : pixel;


endmodule
