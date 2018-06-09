`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:30:23 10/04/2017 
// Design Name: 
// Module Name:    MemInst 
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
module MemInst(
    input [47:0] dir_input,
    output [47:0] dir_output
    );
		
	 integer i;
	 localparam MEM_SIZE = 32; //Tama�o Memoria
	
	 reg [47:0] memRegFile [0:MEM_SIZE];
	 reg [47:0] dir_output_reg;
	 
	 initial begin
		 for(i = 0; i < MEM_SIZE; i = i + 1) memRegFile[i] = 48'b0;
		 
		 memRegFile[0] = 48'h0001;
		 memRegFile[1] = 48'h58CE00000FFA;
		 memRegFile[10] = 48'h8063;
		 memRegFile[14] = 48'h1456;
		 //memRegFile[1] = 16'h1123;
		 //memRegFile[2] = 16'h3302;
		 /*for (i = 2; i < MEM_SIZE; i = i + 1) begin
				memRegFile[i] = 16'h0000;
		 end*/
	 end
	 
	 always @ * begin
		dir_output_reg = memRegFile[dir_input];
	 end
	 
	 assign dir_output = dir_output_reg;

endmodule
