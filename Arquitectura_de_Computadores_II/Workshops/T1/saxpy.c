/* 
 * File:   saxpy.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on Feb 24, 2018
 * Simple SAXPY(Single-precision Alpha*X Plus Y) operation with OpenMP
 *
 * Ussage: 
 * ./argv[0] for default parameters and random vectors or;
 * ./argv[0] <array size>
 */

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

#define FLOAT_RAND_MAX 10000
#define VECTOR_SIZE 1000


void generateFloatVector(long size, float* vector);
void printFloatVector(long size, float* vector);
void SAXPY(long size, float alpha, float* X, float* Y);

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
	float alpha = ((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX;
	// Allocate memmory for the vectors
	float* X = (float*)malloc(sizeof(float)*size);
	float* Y = (float*)malloc(sizeof(float)*size);
	// Generate random vectors
	generateFloatVector(size, X);
	generateFloatVector(size, Y);
	// Print the vectors
	if(printVectors){
		printf("----Y=aX+Y----\na: %f\n", alpha);
		printf("X: ");
		printFloatVector(size, X);
		printf("Y: ");
		printFloatVector(size, Y);
	}
	//Do the actual SAXPY and take the time
	start_time = omp_get_wtime();
	SAXPY(size, alpha, X, Y);
	run_time = omp_get_wtime() - start_time;
	//Print the result
	if(printVectors){
		printf("Y: ");
		printFloatVector(size, Y);
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
 * @param X a vector of floats
 * @param Y a vector of floats
 */
void SAXPY(long size, float alpha, float* X, float* Y){
	long i;
	#ifdef PARALLEL
	#pragma omp parallel for  private(i) shared(size, alpha, X, Y)
	#endif
	for(i = 0; i<size; i++){
		Y[i]=alpha*X[i] + Y[i];
	}
}


/*
 * Function that fills a vector of size "size" with random numbers
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)vector the place where the data will be stored.  
 */
void generateFloatVector(long size, float* vector){
	for(long i=0; i<size;i++){
		vector[i] = ((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX;
	}
}

/*
 * Function that prints a vector on screen
 * @param (INPUT)size the length of the vector
 * @param (INPUT)vector the place where the data will be stored. 
 */
void printFloatVector(long size, float* vector){
	printf("[");
	for(long i=0; i<size;i++){
		printf(" %f ", vector[i]);
	}
	printf("]\n");
}