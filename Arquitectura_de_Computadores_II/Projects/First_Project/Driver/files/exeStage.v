module exeStage(
	input clk,
	input [47:0] pc1,
	input [3:0] flagsALU,
	input [2:0] flagsMEM,
	input [1:0] flagsWB,
	input [5:0] opcode,
	input [31:0] dataOne,
	input [31:0] dataTwo,
	input [31:0] immediate,
	input [4:0] rd,
	output [47:0] pc1_out,
	output [2:0] flagsMEM_out,
	output [1:0] flagsWB_out,
	output [5:0] opcode_out,
	output [47:0] immediate_out,
	output [47:0] result_out,
	output [47:0] datainput_out,
	output [4:0] rd_out,
	output [7:0] pixel1_out,
	output [7:0] pixel2_out,
	output [7:0] pixel3_out,
	output [7:0] pixel4_out
	
);
	
	//OUTPUT muxOperB
	wire [31:0] output_B;
	
	//OUTPUT alu_operands
	wire [31:0] alu_operands_out;
	wire zero_flag;
	
	//OUTPUT mux_pixel1
	wire [7:0] mux_pixel1_out;
	
	//OUTPUT alu_pixel1
	wire [7:0] alu_pixel1_out;
	
	//OUTPUT mux_pixel2
	wire [7:0] mux_pixel2_out;
	
	//OUTPUT alu_pixel2
	wire [7:0] alu_pixel2_out;
	
	//OUTPUT mux_pixel3
	wire [7:0] mux_pixel3_out;
	
	//OUTPUT alu_pixel3
	wire [7:0] alu_pixel3_out;
	
	//OUTPUT mux_pixel4
	wire [7:0] mux_pixel4_out;
	
	//OUTPUT alu_pixel4
	wire [7:0] alu_pixel4_out;
	
	//OUTPUT concat_pixels
	wire [31:0] concat_pixels_out;
	
	//OUTPUT mux_alu_concat
	wire [31:0] mux_alu_concat_out;
		
	muxOperB mB(
		.datB(dataTwo),
		.immediate(immediate),
		.sel_operB(opcode[2]),
		.output_B(output_B)
	);
	
	alu_operands ALU_OP(
		.datA(dataOne),
		.muxB_out(output_B),
		.main_alu(flagsALU[3]),
		.opcode(opcode),
		.zero_flag(zero_flag),
		.alu_operands_out(alu_operands_out)
	);
	
	mux_pixel1 mp1(
		.pixel(dataTwo[7:0]),
		.immediate(immediate),
		.select_pixel1(~opcode[4]),
		.mux_pixel_out(mux_pixel1_out)
	);
	
	alu_pixel1 ap1(
		.operandA(dataOne[7:0]),
		.operandB(mux_pixel1_out),
		.alu_fun(flagsALU[2:0]),
		.alu_out(alu_pixel1_out)
	);
	
	mux_pixel2 mp2(
		.pixel(dataTwo[15:8]),
		.immediate(immediate),
		.select_pixel2(~opcode[4]),
		.mux_pixel_out(mux_pixel2_out)
	);
	
	alu_pixel2 ap2(
		.operandA(dataOne[15:8]),
		.operandB(mux_pixel2_out),
		.alu_fun(flagsALU[2:0]),
		.alu_out(alu_pixel2_out)
	);
	
	mux_pixel3 mp3(
		.pixel(dataTwo[23:16]),
		.immediate(immediate),
		.select_pixel3(~opcode[4]),
		.mux_pixel_out(mux_pixel3_out)
	);
	
	alu_pixel3 ap3(
		.operandA(dataOne[23:16]),
		.operandB(mux_pixel3_out),
		.alu_fun(flagsALU[2:0]),
		.alu_out(alu_pixel3_out)
	);
	
	mux_pixel4 mp4(
		.pixel(dataTwo[31:24]),
		.immediate(immediate),
		.select_pixel4(~opcode[4]),
		.mux_pixel_out(mux_pixel4_out)
	);
	
	alu_pixel4 ap4(
		.operandA(dataOne[31:24]),
		.operandB(mux_pixel4_out),
		.alu_fun(flagsALU[2:0]),
		.alu_out(alu_pixel4_out)
	);
	
	
	concat_pixels cp(
		.pixel1(alu_pixel1_out),
		.pixel2(alu_pixel2_out),
		.pixel3(alu_pixel3_out),
		.pixel4(alu_pixel4_out),
		.vector_out(concat_pixels_out)
	);
	
	
	mux_alu_concat mux_al_c(
		.alu(alu_operands_out),
		.concat(concat_pixels_out),
		.mux_sel(opcode[4]),
		.mux_out(result_out)
	);

	
	assign pixel1_out = alu_pixel1_out;
	assign pixel2_out = alu_pixel2_out;
	assign pixel3_out = alu_pixel3_out;
	assign pixel4_out = alu_pixel4_out;
	
	assign pc1_out = pc1;
	assign immediate_out = immediate;
	assign rd_out = rd;
	assign flagsMEM_out = {zero_flag, flagsMEM[1:0]};
	assign flagsWB_out = flagsWB;
	assign opcode_out = opcode;
	assign datainput_out = dataTwo;

endmodule