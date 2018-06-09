`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:41:51 03/17/2018 
// Design Name: 
// Module Name:    concat_pixels 
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
module concat_pixels(
    input [7:0] pixel1,
    input [7:0] pixel2,
    input [7:0] pixel3,
    input [7:0] pixel4,
    output [31:0] vector_out
    );
	 
	 assign vector_out = {pixel4, pixel3, pixel2, pixel1};

endmodule
