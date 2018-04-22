`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:16:17 03/16/2018 
// Design Name: 
// Module Name:    alu_operands 
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
module alu_operands(
    input [31:0] datA,
    input [31:0] muxB_out,
    input main_alu,
	 input [5:0] opcode,
	 output zero_flag,
    output [31:0] alu_operands_out
    );
	 
	 reg [31:0] result_alu;
	 reg zero_flag_reg;
	 
	 always @ * begin
	 
		case (main_alu)
			1'b0: result_alu = datA - muxB_out; //Resta
			1'b1: result_alu = datA + muxB_out; //Suma
		endcase
		
		case(opcode)
			6'h22 : zero_flag_reg = (result_alu) ? 1 : 0;
			default : zero_flag_reg = (result_alu) ? 0 : 1;
		endcase 
	 
	 end
	 
	 assign alu_operands_out = result_alu;
	 assign zero_flag = zero_flag_reg;
	 

endmodule
