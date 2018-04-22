module IDEXreg(
    input clk,
    input [31:0] dataOne,
    input [31:0] dataTwo,
	 input [31:0] immediate,
    input [3:0] flagsALU,
    input [2:0] flagsMEM,
    input [1:0] flagsWB,
	 input [47:0] pc1,
	 input [4:0] rd_dir,
	 input [5:0] opcode,
    output [31:0] dataOne_out,
    output [31:0] dataTwo_out,
	 output [31:0] immediate_out,
	 output [3:0] flagsALU_out,
    output [2:0] flagsMEM_out,
    output [1:0] flagsWB_out,
    output [47:0] pc1_out,
	 output [4:0] rd_out,
	 output [5:0] opcode_out
    );
	 
	 reg [47:0] pc1_reg;
	 reg [31:0] dataOne_reg, dataTwo_reg, immediate_reg;
	 reg [5:0] opcode_reg;
	 reg [4:0] rd_dir_reg;
	 reg [3:0] flagsALU_reg;
	 reg [2:0] flagsMEM_reg;
	 reg [1:0] flagsWB_reg;
	 
	 
	 always @ (negedge clk) begin	
		dataOne_reg = dataOne;
		dataTwo_reg = dataTwo;
		immediate_reg = immediate;
		pc1_reg = pc1;
		flagsALU_reg = flagsALU;
		flagsMEM_reg = flagsMEM;
		flagsWB_reg = flagsWB;
		rd_dir_reg = rd_dir;
		opcode_reg = opcode;
	 end
	 
	 assign dataOne_out   = dataOne_reg;
	 assign dataTwo_out   = dataTwo_reg;
	 assign immediate_out = immediate_reg;
	 assign flagsALU_out  = flagsALU_reg;
	 assign flagsMEM_out  = flagsMEM_reg;
	 assign flagsWB_out   = flagsWB_reg;
	 assign pc1_out       = pc1_reg;
	 assign rd_out 		 = rd_dir_reg;
	 assign opcode_out 	 = opcode_reg;

endmodule
