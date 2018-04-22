module wbStage(
	input [1:0] flagsWB,
	input [31:0] mem_data,
	input [31:0] direction,
	output [31:0] data_out
);

	Mux_Sel_Dat msd(
		.mem_data(mem_data),
		.calc(direction),
		.sel_dat(flagsWB[0]),
		.output_Y(data_out)
	);

endmodule