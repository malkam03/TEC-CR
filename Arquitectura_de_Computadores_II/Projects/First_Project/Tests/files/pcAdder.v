`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:51:25 10/04/2017 
// Design Name: 
// Module Name:    pcAdder 
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
module pcAdder(
    input [47:0] pc,
    output [47:0] pc1
    );
	 
	localparam MEM_SIZE = 32; //Tamaño Memoria
	
	reg [47:0] pc1_reg;
	
	always @ * begin
		if(pc+48'b1 == MEM_SIZE) pc1_reg = 48'b0;
		else pc1_reg = pc + 48'b1;
	end
	
	assign pc1 = pc1_reg;

endmodule
