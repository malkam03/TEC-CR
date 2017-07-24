`timescale 1ns / 1ps
module ALUcontrol (iFunct, iALUOp, oControlSignal);

// I/O 

input wire [5:0] iFunct;  // funct of the instruction.

input wire [1:0] iALUOp; // The signal we received from control.

output wire [3:0] oControlSignal; // Signal we'll send to the ALU.

reg [3:0] controlSignalReg;

assign oControlSignal= controlSignalReg;
always @(iFunct, iALUOp)
begin
	case (iALUOp)
		2'b00:
			controlSignalReg <=	4'b0010;
		2'b01:
			controlSignalReg <=	4'b0011;
		2'b10:

		begin
			case (iFunct)
				
				6'h18:
					controlSignalReg <=	4'b0111;
				6'h1A:
					controlSignalReg <=	4'b1000;
				6'h24:
					controlSignalReg <=	4'b0000;
				6'h25:
					controlSignalReg <=	4'b0001;
				6'h26:
					controlSignalReg <=	4'b0100;
				6'h27:
					controlSignalReg <=	4'b0101;
				default:
					controlSignalReg <=	4'b0000;
			endcase // case (iFunct)
		end // case: 2'b10
	default:
		controlSignalReg <=	4'b0000;
	endcase // case (iALUOp)
end

endmodule // ALUcontrol