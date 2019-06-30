/** @file simple_calculator.c
 * 
 * @brief Source file with the 2nd workshop solution 
 * @author Malcolm Davis
 */ 
#include <se_math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(char* scriptName){
	printf("Simplest c calculator.\nusage: %s operand operator operand\ne.g: %s 1 x 2\nOr usage: sqrt x\n", scriptName, scriptName);
}


int main(int argc, char** argv){
	if (argc != 3 && argc != 4){
		print_usage(argv[0]);
		return -1;
	}
	if (argc == 3){
		if (!strcmp(argv[1], "sqrt")){
			int x = atoi(argv[2]);
			float result =sqrt_se(&x);
			printf("%f\n",result); 
		}else{
			print_usage(argv[0]);
		}
	}
	if (argc == 4){
		int a = atoi(argv[1]);
		int b = atoi(argv[3]);
		char op = *argv[2];
		switch	(op){
			case '+':
				printf("%d\n",add_se(&a,&b));
				break;
			case '-':
				printf("%d\n",substract_se(&a,&b));
				break;
			case 'x':
				printf("%d\n",multiply_se(&a,&b));
				break;
			case '/':
				printf("%f\n",divide_se(&a,&b));
				break;
			default:
				print_usage(argv[0]);
				return -1;
		}
		return 0;
	}

}