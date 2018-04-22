`timescale 1ns / 1ps

module Proyecto1_ProcesadorVectorial(
	input rst,
	input clk,
	input clk_f,
	output [31:0] prueba
);
	
	wire [31:0] memAddress, memData, outputMem;
	wire rden, wren;


	procesador cpu(
		.rst(rst),
		.clk(clk),
		.clk_f(clk_f),
		.dataMem(outputMem),
		.prueba(prueba),
		.memAddress(memAddress),
		.memDataInput(memData),
		.readEn(rden),
		.writeEn(wren)
	);
	
//	memory mem(
//		.address(memAddress),
//		.clock(clk),
//		.data(memData),
//		.rden(rden),
//		.wren(wren),
//		.q(outputMem)
//	);
//	
	
endmodule