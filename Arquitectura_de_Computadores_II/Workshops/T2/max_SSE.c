/* 
 * File:   max_SSE.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on Apr 20, 2018
 * 16 bit values vector max 
 *
 * Usage: 
 * ./max for default parameters and random vectors or;
 * ./max v1.1 v1.2 v1.3 v1.4 v1.5 v1.6 v1.7 v1.8 v2.1 v2.2 v2.3 v2.4 v2.5 v2.6 v2.7 v2.8 [ v3.1 ...]
 */
#include <emmintrin.h>//v3
#include <smmintrin.h>//v4
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
	if (((argc-1)%0)!=0 || (int)((argc-1)/8) == 1){
		usage();
		return -1;
	}
	__m128i vector1, vector2, result;
	int v1[8], v2[8];
	if(argc == 1){
		for (int i = 0; i < 8; ++i)
		{
			v1[i] = rand();
			v2[i] = rand();
		}
	} else{
		for (int i = 0; i < 8; ++i)
		{
			v1[i]=atoi(argv[i+1]);
			v2[i]=atoi(argv[i+9]);
		}
	}
	vector1 = v1;
	vector2 = v2;
}

void usage(){
	printf("./max for default parameters and random vectors or;\n\
  			./max v1.1 v1.2 v1.3 v1.4 v1.5 v1.6 v1.7 v1.8 v2.1 v2.2 v2.3 v2.4 v2.5 v2.6 v2.7 v2.8 [ v3.1 ...]");
}