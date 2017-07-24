`timescale 1ns / 1ps

module main(cycle, PC, inst, alu_out, mem_out, clock,
regdst, aluop, alusrc, branch, memread,
memwrite, regwrite, memtoreg, zero);
// input/output
input clock;
output[31:0] cycle, PC, inst, alu_out, mem_out;
output regdst, alusrc, branch, memread, memwrite, regwrite, memtoreg;
output[1:0] aluop;
output zero;

// for debug
reg[31:0] cycle=32'd0;

always @ (posedge clock) begin
 cycle = cycle + 1;
 end
// control variables
wire [1:0] ALUOp, ALUSrcB, PCSource;
wire PCWriteCond, PCWrite, lorD, MemRead, MemWrite, MemtoReg, RWrite,
ALUSrcA, RegWrite, RegDst;

// data path wires
 wire[31:0] pcmuxout, MemData, IROut, MDROut, MDRMux, SignExtendOut,
SES4Out, RD1, RD2, ARegOut, BRegOut, AMuxOut, BMuxOut, ALUResult,
ALURegOut, nextpc, pcshift2out;
 reg[31:0] PC=128;
 wire [4:0] instructionmuxout;

 //stuff to update PC
 wire PCWriteEnable;
 wire tempPCvar;
 
 
 //pcMux
 muxTwoToOne muxPC(IorD,PC,ALURegOut,pcmuxout);
 
 
 //memory
DataMemory DataMemory1(clock, pcmuxout, BRegOut, MemWrite, MemRead,MemData); 

//Instruction register
 IR IR1(IRWrite, MemData, IROut ,clock); 
 
 //Memory Data Register
 MDR MDR1(MemData, MDROut ,clock);
 
 
 //Controller
 controller Control1(clock, Reset, IROut[31:26], PCWriteCond, PCWrite, lorD,MemRead, MemWrite, MemtoReg, IRWrite, PCSource, ALUOp, ALUSrcB,ALUSrcA, RegWrite, RegDst); 
 
 //instruction decoding
 muxTwoToOne muxRegi(RegDst,IROut[20:16],IROut[15:11],instructionmuxout);
 muxTwoToOne muxmem(MemtoReg,ALURegOut, MDROut,MDRMux);
 
 //Registers
 RegFile registers(IROut[25:21],IROut[20:16],instructionmuxout,RegWrite,MDRMux,RD1,RD2,clock);
 ABregister A(RD1, ARegOut ,clock);
 ABregister B(RD2, BRegOut ,clock); 
 
 //muxes for ALU input
 muxTwoToOne muxA(ALUSrcA,PC,ARegOut,AMuxOut);
 
 //ALU controller and ALU
 wire [3:0] Operation;
 ALUcontrol ALUControl1(IROut[5:0],ALUOp,Operation);
 ALU alu1(AMuxOut, BRegOut, Operation, ALUResult);
 ALUOut aluout1(ALUResult, ALURegOut ,clock); 
 assign nextpc=ALUResult;
 
 //updating pc
assign tempPCvar=zero&PCWriteCond;
assign PCWriteEnable=tempPCvar|PCWrite;
always@ (posedge clock) begin
 if(PCWriteEnable==1'b1)begin
PC <= nextpc;
end
end 
endmodule 