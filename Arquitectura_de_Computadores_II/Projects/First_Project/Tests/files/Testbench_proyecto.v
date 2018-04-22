module Testbench_proyecto(
	input clk,
	input rst,
	output [31:0] pc,
	output [47:0] inst_out_fe
);


	//OUTPUTS fetchStage
	//wire [47:0] inst_out_fe; //pc_out_fecthStage

	fetchStage FS(
		.clk(clk),
		.clk_faster(clk),
		.rst(rst),
		.pc1_in(pc),//pc1_out_exmem_reg),
		.branch(0),
		.sel_pc(0),//opcode_out_exmem_reg[5] & flagsMEM_out_exmem_reg[2]),
		.pc1(pc),
		.instruction(inst_out_fe)
	);
	
	

	initial begin
		// Initialize Inputs
		rst = 1;
		clk = 1;

		// Wait 100 ns for global reset to finish
		#100;
      
		rst = 0;
		
	end
	
	always begin
		#10  clk = ~clk; 
	end

endmodule 