/* 
 * File:   saxpy_neon.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on May 12, 2018
 * Simple SAXPY(Single-precision Alpha*X Plus Y) operation with OpenMP and NEON
 *
 * Ussage: 
 * ./argv[0] for default parameters and random vectors or;
 * ./argv[0] <array size>
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <arm_neon.h>
#include <omp.h>

#define FLOAT_RAND_MAX 10000
#define VECTOR_SIZE 100000

void generateIntVector(int16_t *vector, long size);
void printIntVector(int16_t *vector, long size);
int16_t* SAXPY(long size, int16_t *alpha, int16_t *X, int16_t *Y);


/*
 * Main method, retrive command line options and run the saxpy
 */
int main(int argc, char const *argv[])
{     
    const int printVectors = getenv("PRINT_VECTORS") ? 1 : 0;
    
    double start_time, run_time;
    srand(time(NULL));

    // If the vector size is inserted then use it if not then use the default 
    long size = argc > 1 && atol(argv[1]) > 0 ? atol(argv[1]) : VECTOR_SIZE;
    int alpha = ceil(((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX);

    // Allocate memmory for the vectors
    int16_t* Y=(int16_t*)malloc(sizeof(int16_t)*size);
    int16_t* X=(int16_t*)malloc(sizeof(int16_t)*size);
    int16_t* A=(int16_t*)malloc(sizeof(int16_t)*size);
    // Generate random vectors
    generateIntVector(Y, size);
    generateIntVector(X, size);
    memset( A, alpha, size*sizeof(int16_t));
    int16_t *result;
    result= SAXPY(size, A, X, Y);
    start_time = omp_get_wtime();
    for (int j = 0; j < size; ++j){
        result[j] = alpha*X[j] + Y[j];
    }
    run_time = omp_get_wtime() - start_time;
    printf("\n Serial run time with size %ld: %f s \n", size, run_time);
    free(Y);
    free(X);
    free(A);
    return 0;
}

/*
 * SAXPY Function R = aX + Y
 * @param size the lenght of the vectors
 * @param alpha the const to scale the vector X
 * @param X a vector of floats
 * @param Y a vector of floats
 */
int16_t* SAXPY(long size, int16_t *alpha, int16_t *X, int16_t *Y)
{
    int16_t *result = (int16_t*)malloc(sizeof(int16_t)*size);
    int i=0, j=0;
    int16x4_t vecY;
    int16x4_t vecA;
    int16x4_t vecX;
    int16x4_t r ;
    double start_time, runTime;
    start_time = omp_get_wtime();
    #ifdef PARALLEL
    #pragma omp parallel for  private(i, j) shared(size, alpha, X, Y)
    #endif
    for (j=0; j < size; j+=4)
    {
        vecY = vld1_s16(Y);
        vecA = vld1_s16(alpha);
        vecX = vld1_s16(X);
        r = vmla_s16(vecY, vecA, vecX);
        result[i++]=r[0];
        result[i++]=r[1];
        result[i++]=r[2];
        result[i++]=r[3];
        Y+=4;
        alpha+=4;
        X+=4;
    }
    runTime = omp_get_wtime() - start_time;
    #ifdef PARALLEL
        printf("\n Parallel run time with size %ld: %f s \n",size, runTime);
    #endif
    return result;
}

/*
 * Function that fills a vector of size "size" with random numbers
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)vector the place where the data will be stored.  
 */
void generateIntVector(int16_t *vector, long size)
{   
    long i;
    #ifdef PARALLEL
    #pragma omp parallel for  private(i) shared(size, vector)
    #endif
    for(i=0; i<size;i++){
        vector[i] = ((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX;
    }
}

/*
 * Function that prints a vector on screen
 * @param (INPUT)size the length of the vector
 * @param (INPUT)vector the place where the data will be stored. 
 */
void printIntVector(int16_t *vector, long size)
{   
    printf("[");
    for(long i=0; i<size;i++){
        printf(" %hd ", vector[i]);
    }
    printf("]\n");
}