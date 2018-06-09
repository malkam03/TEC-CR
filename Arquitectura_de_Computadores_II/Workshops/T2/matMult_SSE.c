/* 
 * File:   matMult.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on Apr 20, 2018
 * 4x4 matrix multiplication
 *
 * Usage: 
 * ./matMult for default parameters and random matrixes or;
 * ./matMult v1.1.1 v1.1.2 ... v1.1.4 ... v1.2.1 v1.2.2 ... v1.2.4 ... v2.4.1 v2.4.2 ... v2.4.4 
 */
#include "xmmintrin.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void usage(){
	printf("Usage:\n ./matMult for default parameters and random matrixes or;\n\
./matMult v1.1.1 v1.1.2 ... v1.1.4 ... v1.2.1 v1.2.2 ... v1.2.4 ... v2.4.1 v2.4.2 ... v2.4.4 \n");
}


/*
 * Prints a __m128i vector on console
 * @param v the vector to print
 */
void printVector(__m128i* v){
	float * pointer = (float*)v;
	for (int i = 0; i < 4; ++i)
	{
		printf("%f\t", *pointer);
		pointer++;
	}
	printf("\n");
}

/*
 * Prints a 4x4 float matrix on console
 * @param matrix pointer to the matrix to print
 */
void prinMatrix(float* matrix){
	float * pointer = matrix;
	for (int i = 0; i < 16; ++i)
	{
		printf("%f\t", *pointer);
		if((i+1)%4==0)
			printf("\n");
		pointer++;
	}
	printf("\n");
}

/*
 * Transpose a 4x4 float matrix
 * @param src the one to transpose
 * @param out the one with the transpose result
 */

void transposeMatrix(float* src, float* dst){
	//#pragma omp parallel for
	for (int i = 0; i < 16; i++)
	{
		dst[i]=src[(int)(floor(i/4)+4*(i%4))];
	}
	printf("\n");
}

/*
 * Main method, retrive command line options, and multiplies the matrixes
 */
int main(int argc, char ** argv){
	//If the count of the input is not a 32(16x2(4x4)) greater than 2, then exit
	if (argc != 33 && argc != 1){
		usage();
		return -1;
	}
	__m128 matrix1, matrix2, tmpRes, tmpV1, tmpV2;
	static float m1[16], m2[16], m2t[16], result[16], *tmpPointer;
	if(argc == 1){
		srand (time(NULL));
		//If no arguments then generate random matrices
		#pragma omp parallel for
		for (int i = 0; i < 16; ++i)
		{
			m1[i] = rand();
			m2[i] = rand();
		}
	} else{
		//If arguments then set the values into a vector
		#pragma omp parallel for
		for (int i = 0; i < 16; ++i)
		{
			m1[i]=atof(argv[i+1]);
			m2[i]=atof(argv[i+17]);
		}
	}
	matrix1 = *(__m128*)m1;
	matrix2 = *(__m128*)m2;
	printf("Matrix 1: \n");
	prinMatrix(m1);
	printf("Matrix 2: \n");
	prinMatrix(m2);
	transposeMatrix(m2, m2t);
	#pragma omp parallel for private(tmpV1, tmpV2, tmpPointer, tmpRes)
	for (int i = 0; i < 16; ++i)
	{
		tmpV1 = *(((__m128*)m1)+(int)floor(i/4));
		tmpV2 = *(((__m128*)m2t)+i%4);
		tmpRes = _mm_mul_ps(tmpV1, tmpV2);
		tmpPointer = (float*)&tmpRes;
		result[i] =0;
		for (int j = 0; j < 4; ++j)
		{
			result[i] += *(tmpPointer++);
		}

	}
	printf("Result *********************** \n");
	printf("Result: \n");
	prinMatrix(result);
}