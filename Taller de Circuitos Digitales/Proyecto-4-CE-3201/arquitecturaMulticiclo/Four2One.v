`timescale 1ns / 1ps
module Four2One(Control, A, B, C, D, Out);
input [1:0] Control;
input [31:0] A, B, C, D;
output [31:0] Out;
reg [31:0] temp1, temp2, Out;

 always @ (Control, A, B, C, D) 
 begin
 case(Control)
 2'b00:
	Out=A;
 2'b01:
	Out=B;
 2'b10:
	Out=C;
 2'b11:
	Out=D;
 default:
	Out=A;
 endcase 
 end
endmodule
