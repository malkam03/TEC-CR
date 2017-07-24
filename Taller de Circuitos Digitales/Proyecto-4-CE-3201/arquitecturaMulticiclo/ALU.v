`timescale 1ns / 1ps
/* Control lines	|	Function
 * ----------------------------------------------
 * 0000			|	AND
 * 0001			|	OR
 * 0010			|	add
 * 0011			|	subtract
 * 0100			|	XOR
 * 0101			|	NOR
 * 0111           MULT
 * 1000           DIV
 */
module ALU (iA, iB, iControlSignal,oALUresult);


/* I/O type definition */

input wire [31:0] iA, iB;
input wire [3:0] iControlSignal;
output wire [31:0] oALUresult;


wire [31:0] tmpA, tmpB;
wire [31:0] div;
wire [63:0] mult;
reg [31:0] ALUresultReg= 32'b0;
assign oALUresult=ALUresultReg;
/* Helps treating the signal in several of the operations */
assign tmpA	= (iA[31]) ? ~iA + 1 : iA;
assign tmpB	= (iB[31]) ? ~iB + 1 : iB;
assign mult	= tmpA*tmpB;
assign div = tmpA/tmpB;
always @(iA, iB,iControlSignal,oALUresult)
begin
	case (iControlSignal)
		4'b0000:
			ALUresultReg	<= iA & iB;
		4'b0001:
			ALUresultReg	<= iA | iB;
		4'b0010:
		   begin
			ALUresultReg	<= iA + iB;
//			oOverflow = ((iA[31] == 0 && iB[31] == 0 &&  oALUresult[31] == 1) || (iA[31] == 1 && iB[31] == 1 && oALUresult[31] == 0)); 
		   end
		4'b0011:
		  begin
			ALUresultReg	<= iA - iB;
//			oOverflow = ((iA[31] == 0 && iB[31] == 1 && oALUresult[31]== 1)|| (iA[31] == 1 && iB[31] == 0 && oALUresult[31] == 0));
		  end
		
		4'b0100:
			ALUresultReg	<= iA ^ iB;
		4'b0101:
			ALUresultReg	<= ~(iA | iB);
// para testes de simulacao
		4'b0111:
			ALUresultReg	<= mult[31:0];
		4'b1000:
			ALUresultReg	<= div[31:0];
//
		default:
			ALUresultReg<= 32'b0;
	endcase
end



endmodule