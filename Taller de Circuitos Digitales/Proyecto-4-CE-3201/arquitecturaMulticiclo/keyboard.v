`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    04:19:22 06/19/2017 
// Design Name: 
// Module Name:    keyboard 
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
module keyboard(
    output reg[31:0] A,
    output reg[31:0] B,
    output reg[4:0] op,
    input forward
    );
	 
reg [2:0] test = 4'b000;
always @(posedge forward)
	begin
		if (test >= 7) 
			test <= 3'b000;
		else 
			test <= test+1;
		case(test)
		  3'b000 : 
		  begin
			  A = 5;
			  B = 20;
			  op = 1;
		  end
		  3'b001 : 
		  begin
			  A = 10;
			  B = 2;
			  op = 2;
		  end
		  3'b010 : 
		  begin
			  A = 15;
			  B = 11;
			  op = 3;
		  end
		  3'b011 : 
		  begin
			  A = 55;
			  B = 20;
			  op = 4;
		  end
		  3'b100 : 
		  begin
			  A = 6;
			  B = 22;
			  op = 5;
		  end
		  3'b101 : 
		  begin
			  A = 8;
			  B = 1;
			  op = 6;
		  end
		  3'b110 : 
		  begin
			  A = 0;
			  B = 12;
			  op = 7;
		  end
		  3'b111 : 
		  begin
			  A = 14;
			  B = 98;
			  op = 8;
		  end
		endcase
	end
endmodule
