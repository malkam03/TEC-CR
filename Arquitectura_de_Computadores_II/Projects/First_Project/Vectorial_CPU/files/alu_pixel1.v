`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:54:18 03/17/2018 
// Design Name: 
// Module Name:    alu_pixel1 
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
module alu_pixel1(
    input [7:0] operandA,
    input [7:0] operandB,
    input [2:0] alu_fun,
    output [7:0] alu_out
    );

	localparam [2:0] op_add = 3'd1, op_sub = 3'd2, op_xor = 3'd3, op_shift_right = 3'd4, op_shift_left = 3'd5,
	op_shift_right_circular = 3'd6, op_shift_left_circular = 3'd7;
	reg [7:0] result_reg, tmp_bit;
	reg [8:0] tmp_overflow;
	
	always @ * begin
		
		case(alu_fun)
			op_add : begin
							tmp_overflow = operandA + operandB;
							if(tmp_overflow > 255) result_reg = tmp_overflow - 255;
							else result_reg = tmp_overflow[7:0];
						end
			op_sub : begin
							if(operandA < operandB) result_reg = 255 + operandA - operandB;
							else result_reg = operandA - operandB;
						end
			op_xor : result_reg = operandA ^ operandB;
			op_shift_right : result_reg = operandA >> operandB;
			op_shift_left : result_reg = operandA << operandB;
			op_shift_right_circular : begin
												tmp_bit = operandA << (8-operandB);
												result_reg = operandA >> operandB;
												result_reg = tmp_bit + result_reg;
											  end
			op_shift_left_circular : begin
												tmp_bit = operandA >> (8-operandB);
												result_reg = operandA << operandB;
												result_reg = tmp_bit + result_reg;
											  end
		endcase
		
	end
	
	assign alu_out = result_reg;

endmodule
