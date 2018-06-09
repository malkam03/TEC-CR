module fetchStage(
	input clk,
	input clk_faster,
	input rst,
	input [47:0] pc1_in,
	input [47:0] branch,
	input sel_pc,
	output [47:0] pc1,
	output [47:0] instruction
);
	
	wire [47:0] pc_out_reg, mux_selPC_out;
	
	Mux_Sel_PC mPC(
		.output_ALU(branch),
		.output_PC1(pc1_in),
		.sel_pc(sel_pc),
		.output_sel_pc(mux_selPC_out)
	);
	
	RegPC rPC(
		.pc_in(mux_selPC_out),
		.clk(clk),
		.rst(rst),
		.pc_out(pc_out_reg)
	);
	
	pcAdder pcA(
		.pc(pc_out_reg),
		.pc1(pc1)
	);
	
	/*
	MemInst MI(
		.dir_input(pc_out_reg),
		.dir_output(instruction)
	);*/
	
	memInstruction memI(
		.address(pc_out_reg),
		.clock(clk_faster),
		.q(instruction)
	);

endmodule