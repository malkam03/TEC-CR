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

#define FLOAT_RAND_MAX 10000
#define VECTOR_SIZE 1000


void generateFloatVector(int size, float* vector);
void printFloatVector(int size, float* vector, int writeFile, const char* fileName);
void getDataFromFile(const char* fileName, float* alphas,float* vectors, int* sizes, int * amount);
void SAXPY(int size, float alpha, float* X, float* Y);

/*
 * Main method, retrive command line options, create the threads
 */
int main(int argc, char const *argv[])
{
	const char* fileName = getenv("TMPFILE");
	const int writeFile = getenv("WRITE_FILE") ? 1 : 0;
	const int readFile = getenv("READ_FILE") ? 1 : 0;
	double start_time, run_time;
	srand(time(NULL));
	if (readFile){
		float *alphas;
		float *vectors;
		int* sizes;
		int amount=0;
		int ofset=0;
		// Retrive all the vectors, alphas and sizes from the file
		getDataFromFile(fileName, alphas, vectors, sizes, &amount);
		// For every X, Y do the SAXPY
		for(int i=0; i<amount/2; i++){
			float *X = vectors+ofset;
			float *Y = vectors+ofset+sizes[i];
			float alpha = alphas[i];
			start_time = omp_get_wtime();
			SAXPY(sizes[i], alpha, X, Y);
			run_time = omp_get_wtime() - start_time;
			printFloatVector(sizes[i], Y, 0, fileName);
		}
		free(alphas);
		free(vectors);
		free(sizes);
	}else{
		int size = argc > 1 && atoi(argv[1]) > 0 ? atoi(argv[1]) : VECTOR_SIZE;
		float alpha = ((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX;
		float* X = (float*)malloc(sizeof(float)*size);
		float* Y = (float*)malloc(sizeof(float)*size);
		printFloatVector(size, Y, 0, fileName);
		printFloatVector(size, Y, 0, fileName);
		start_time = omp_get_wtime();
		SAXPY(size, alpha, X, Y);
		run_time = omp_get_wtime() - start_time;
		printFloatVector(size, Y, 0, fileName);
		free(Y);
		free(X);
	}
	return 0;
}



void SAXPY(int size, float alpha, float* X, float* Y){
	
}


void getDataFromFile(const char* fileName, float* alphas,float* vectors, int* sizes, int * amount){
	
}



/*
 * Function that fills a vector of size "size" with random numbers
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)vector the place where the data will be stored.  
 */
void generateFloatVector(int size, float* vector){
	for(int i=0; i<size;i++){
		vector[i] = ((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX;
	}
}

/*
 * Function that prints a vector on screen and in file 
 * @param (INPUT)size the length of the vector
 * @param (INPUT)vector the place where the data will be stored. 
 */
void printFloatVector(int size, float* vector, int writeFile, const char* fileName){
	printf("\n[");
	char buffer[size];
	for(int i=0; i<size;i++){
		printf(" %f ", vector[i]);
		if (writeFile) sprintf(buffer, " %f", vector[i]);
	}
	printf("]\n");
	if (writeFile){
		// Write buffer in file
	}
}