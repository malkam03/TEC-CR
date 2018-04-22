module decoStage(
	input clk,
	input rst,
	input [47:0] pc1,
	input [5:0] opcode,
	input [4:0] rd,
	input [4:0] rs,
	input [4:0] rt,
	input [31:0] immediate,
	input flagsDECO,
	input [3:0] flagsALU,
	input [2:0] flagsMEM,
	input [1:0] flagsWB,
	input [4:0] dir_wr, //WB
	input [31:0] data_input, //WB
	input reg_wr, //WB
	output [47:0] pc1_out,
	output [3:0] flagsALU_out,
	output [2:0] flagsMEM_out,
	output [1:0] flagsWB_out,
	output [5:0] opcode_out,
	output [31:0] dataOne,
	output [31:0] dataTwo,
	output [31:0] immediate_out,
	output [4:0] rd_out,
	output [31:0] prueba
);

	BancoRegistros BR(
		.clk(clk),
		.rst(rst),
		.dir_a(rs),
		.dir_b(rt),
		.dir_wra(dir_wr),
		.di(data_input),
		.reg_rd(flagsDECO),
		.reg_wr(reg_wr),
		.doa(dataOne),
		.dob(dataTwo),
		.prueba(prueba)
	);

	assign pc1_out = pc1;
	assign flagsALU_out = flagsALU;
	assign flagsMEM_out = flagsMEM;
	assign flagsWB_out = flagsWB;
	assign opcode_out = opcode;
	assign immediate_out = immediate;
	assign rd_out = rd;

endmodule