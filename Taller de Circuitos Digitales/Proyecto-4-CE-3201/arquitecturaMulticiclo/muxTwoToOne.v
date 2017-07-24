`timescale 1ns / 1ps
module muxTwoToOne(con,a,b,salida);
 input con; 
 input a,b;
 output reg salida;
 always @*
 begin
 case(con)
  1'b0:
		salida <= a;
  1'b1:
		salida <= b;
	default:
      salida <=32'b0;	
  endcase
  end
 endmodule
