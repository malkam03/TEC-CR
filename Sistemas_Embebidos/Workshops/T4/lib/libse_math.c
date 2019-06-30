/** @file se_math.c
 * 
 * @brief Source file with the 2nd workshop solution 
 * @author Malcolm Davis
 */ 

#include <se_math.h>
#include <math.h>


int add_se(int* a, int* b){
	return (*a)+(*b);
}
int substract_se(int* a, int* b){
	return (*a)-(*b);
}
int multiply_se(int* a, int* b){
	return (*a)*(*b);
}
float divide_se(int* a, int* b){
	return (float)(*a)/(*b);
}
float sqrt_se(unsigned int * x){
	return sqrt(*x);
}