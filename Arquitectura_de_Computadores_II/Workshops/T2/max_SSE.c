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
#include <time.h>

void usage(){
	printf("Usage:\n ./max for default parameters and random vectors or;\n\
./max v1.1 v1.2 v1.3 v1.4 v1.5 v1.6 v1.7 v1.8 v2.1 v2.2 v2.3 v2.4 v2.5 v2.6 v2.7 v2.8 [ vn.1 ...]\n");
}

/*
 * Prints a __m128i vector on console
 * @param v the vector to print
 */
void printVector(__m128i* v){
	int16_t * pointer = (int16_t*)v;
	for (int i = 0; i < 8; ++i)
	{
		printf("%d\t", *pointer);
		pointer++;
	}
	printf("\n");
}

/*
 * Main method, retrive command line options, and loops comparing vectors
 */
int main(int argc, char ** argv){
	//If the count of the input is not a multiple of 8 greater than 2, then exit
	if (((argc-1)%8)!=0 || (int)((argc-1)/8) == 1){
		usage();
		return -1;
	}
	__m128i *vector1,* vector2, result;
	static int16_t v1[8], v2[8];
	if(argc == 1){
		srand (time(NULL));
		//If no arguments then generate random vectors
		#pragma omp parallel for
		for (int i = 0; i < 8; ++i)
		{
			v1[i] = rand()%32767;
			v2[i] = rand()%32767;
		}
	} else{
		//If arguments then set the values into a vector
		#pragma omp parallel for
		for (int i = 0; i < 8; ++i)
		{
			v1[i]=atoi(argv[i+1]);
			v2[i]=atoi(argv[i+9]);
		}
	}
	vector1 = (__m128i*)v1;
	vector2 = (__m128i*)v2;
	printf("Vector 1: ");
	printVector(vector1);
	printf("Vector 2: ");
	printVector(vector2);
	result = _mm_max_epi16(*vector1, *vector2);
	//If there are more than 2 vectors, loop and compare
	if((int)((argc-1)/8) >2){
		for (int i = 2; i < (argc-1)/8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				v1[j]=*((int16_t*)(&result)+j);
				v2[j]=atoi(argv[i*8+j+1]);
			}
			vector1 = (__m128i*)v1;
			vector2 = (__m128i*)v2;
			printf("Vector %d: ", i+1);
			printVector(vector2);
			result = _mm_max_epi16(*vector1, *vector2);
		}
	}
	printf("Result *********************** \n");
	printf("Result: ");
	printVector(&result);
}

