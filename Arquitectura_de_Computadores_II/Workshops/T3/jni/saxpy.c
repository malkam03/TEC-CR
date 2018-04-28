/* 
 * File:   saxpy.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on Feb 24, 2018
 * Simple SAXPY(Single-precision Alpha*X Plus Y) operation with OpenMP
 *
 * Ussage: 
 * ./argv[0] for default parameters and random vectors or;
 * ./argv[0] <runing time from 1 to 10> <max array size from 1 to 100> <sampling time> <printing samples time> <number of threads even number>
 */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <arm_neon.h>
#define FLOAT_RAND_MAX 10000
#define VECTOR_SIZE 1000


void generateIntVector(long size, int16_t* vector);
void printIntVector(long size, int16_t* vector);
void SAXPY(long size, const int16_t alpha, int16_t* X, int16_t* Y);

/*
 * Main method, retrive command line options, create the threads
 */
int main(int argc, char const *argv[])
{
	const int printVectors = getenv("PRINT_VECTORS") ? 1 : 0;
	double start_time, run_time;
	srand(time(NULL));
	// If the vector size is inserted then use it if not then use the default 
	long size = argc > 1 && atol(argv[1]) > 0 ? atol(argv[1]) : VECTOR_SIZE;
	const int alpha = ((int16_t)rand()/(int16_t)(RAND_MAX)) * FLOAT_RAND_MAX;
	if (size%4 != 0)
		printf("The size of the vector must be a multiple of 4\n");
		return -1;
	// Allocate memmory for the vectors

	int16_t* X = (int16_t*)malloc(sizeof(int16_t)*size);
	int16_t* Y = (int16_t*)malloc(sizeof(int16_t)*size);
	// Generate random vectors
	generateIntVector(size, X);
	generateIntVector(size, Y);
	// Print the vectors
	if(printVectors){
		printf("----Y=aX+Y----\na: %d\n", alpha);
		printf("X: ");
		printIntVector(size, X);
		printf("Y: ");
		printIntVector(size, Y);
	}
	//Do the actual SAXPY and take the time
	start_time = omp_get_wtime();
	SAXPY(size, alpha, X, Y);
	run_time = omp_get_wtime() - start_time;
	//Print the result
	if(printVectors){
		printf("Y: ");
		printIntVector(size, Y);
	}
	printf("Size: %ld Seconds: %f \n", size, run_time);
	// Free the allocated memmory
	free(Y);
	free(X);
	return 0;
}


/*
 * SAXPY Function Y = aX + Y
 * @param size the lenght of the vectors
 * @param alpha the const to scale the vector X
 * @param X a vector of int16_t
 * @param Y a vector of int16_t
 */
void SAXPY(long size, const int alpha, int16_t* X, int16_t* Y){
	long i;
	#ifdef PARALLEL
	#pragma omp parallel for  private(i) shared(size, alpha, X, Y)
	#endif
	for(i = 0; i<size; i+=4){
		int16x4_t a = vld1_s16(X);
		int16x4_t b = vdup_n_s16(Y);
		int16x4_t res = vdup_n_s16(Y);
		vmla_lane_s16(a, b, res, alpha);
	}
}


/*
 * Function that fills a vector of size "size" with random numbers
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)vector the place where the data will be stored.  
 */
void generateIntVector(long size, int16_t* vector){
	for(long i=0; i<size;i++){
		vector[i] = ((int16_t)rand()/(int16_t)(RAND_MAX)) * FLOAT_RAND_MAX;
	}
}

/*
 * Function that prints a vector on screen
 * @param (INPUT)size the length of the vector
 * @param (INPUT)vector the place where the data will be stored. 
 */
void printIntVector(long size, int16_t* vector){
	printf("[");
	for(long i=0; i<size;i++){
		printf(" %d ", vector[i]);
	}
	printf("]\n");
}