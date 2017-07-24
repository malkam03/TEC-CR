`timescale 1ns / 1ps
module controller (Clk, Reset, Op, PCWriteCond, PCWrite, IorD, MemRead, MemWrite,
MemtoReg, IRWrite, PCSource, ALUOp, ALUSrcB, ALUSrcA, RegWrite, RegDst);

input [5:0] Op;
input Clk, Reset;
output [1:0] ALUOp, ALUSrcB, PCSource;
output PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite,
ALUSrcA, RegWrite, RegDst;
 reg [1:0] ALUOp, ALUSrcB, PCSource;
reg PCWriteCond, PCWrite, IorD,MemRead, MemWrite,MemtoReg, IRWrite,
ALUSrcA, RegWrite, RegDst;
 reg [4:0] state =0, nextstate;
parameter S0=0;
parameter S1=1;
parameter S2=2;
parameter S3=3;

 always@(posedge Clk) begin

 state=nextstate;

 end
 always @(state, Op) begin

 case(state)
S0: begin
 IorD= 1'b0; 
 MemRead=1'b1;
 ALUSrcA=1'b0;
 IRWrite=1'b1;
 ALUSrcB=2'b01;
 ALUOp= 2'b00;
 PCWrite=1'b1;
 PCSource=2'b00;
 nextstate=S1;
 RegWrite = 1'b0;
 MemWrite=1'b0;
 PCWriteCond= 1'b0;
 MemtoReg=1'b0;
end

S1: begin
 MemRead=1'b0; 
 IRWrite=1'b0;
 ALUSrcA=1'b0;
 ALUSrcB=2'b11;
 PCWrite=1'b0;
 ALUOp= 2'b00;
 
 if(Op==6'b000000) begin // if R type instruction
 nextstate=S2;
 end


end

S2: begin
 ALUSrcA= 1'b1;
 ALUSrcB= 2'b00;
 ALUOp = 2'b10;
 nextstate = S3;

end

S3: begin
 RegDst= 1'b1;
 RegWrite = 1'b1;
 MemtoReg = 1'b0;
 nextstate= S0;

 end
 endcase
 end
 endmodule 
