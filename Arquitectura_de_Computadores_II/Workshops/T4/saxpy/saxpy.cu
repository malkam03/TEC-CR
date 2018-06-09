/* 
 * File:   saxpy.cu
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on May 13, 2018
 * Simple SAXPY(Single-precision Alpha*X Plus Y) operation with CUDA
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
#include <omp.h>

#define FLOAT_RAND_MAX 10000
#define VECTOR_SIZE 100000
#define BLOCK_SIZE 16

/*
 *GPU KERNEL
 */
__global__
void saxpy_cuda(long n, float a, float *x, float *y)
{
  long i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) y[i] = a*x[i] + y[i];
}

void generateFloatVector(float *vector, long size);
void printIntVector(float *vector, long size);
void SAXPY(long size, float alpha, float *X, float *Y);
void copyVector(float *dest, float *src, long size);


/*
 * Main method, retrive command line options and run the saxpy
 */
int main(int argc, char const *argv[])
{     
    const int printVectors = getenv("PRINT_VECTORS") ? 1 : 0;
    
    srand(time(NULL));

    // If the vector size is inserted then use it if not then use the default 
    long size = argc > 1 && atol(argv[1]) > 0 ? atol(argv[1]) : VECTOR_SIZE;
    float alpha = ((float)rand()/(float)(RAND_MAX)) * FLOAT_RAND_MAX;

    // Allocate memory for the vectors
    float *H_Y, *H_YY, *H_X;
    cudaMallocHost((void **) &H_Y, sizeof(float)*size);
    cudaMallocHost((void **) &H_YY, sizeof(float)*size);
    cudaMallocHost((void **) &H_X, sizeof(float)*size);
    // Generate random vectors
    generateFloatVector(H_Y, size);
    generateFloatVector(H_X, size);
    copyVector(H_YY, H_Y, size);

    //Timing
    float gpu_elapsed_time_ms, cpu_elapsed_time_ms;

    // some events to count the execution time
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // start to count execution time of GPU version
    cudaEventRecord(start, 0);
    //Allocate memory for the vectors on device
    float* D_X, *D_Y;
    cudaMalloc((void **) &D_X, sizeof(float)*size);
    cudaMalloc((void **) &D_Y, sizeof(float)*size);

    // copy matrix A and B from host to device memory
    cudaMemcpy(D_X, H_X, sizeof(float)*size, cudaMemcpyHostToDevice);
    cudaMemcpy(D_Y, H_Y, sizeof(float)*size, cudaMemcpyHostToDevice);

    unsigned int grid_cols = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    dim3 dimGrid(grid_cols, 1);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);

    // Launch kernel
    saxpy_cuda<<<dimGrid, dimBlock>>>(size, alpha, D_X, D_Y);
    // Transefr results from device to host 
    cudaMemcpy(H_Y, D_Y, sizeof(float)*size, cudaMemcpyDeviceToHost);
    cudaThreadSynchronize();
    // time counting terminate
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    // compute time elapse on GPU computing
    cudaEventElapsedTime(&gpu_elapsed_time_ms, start, stop);
    printf("Time elapsed on saxpy of %ld on GPU: %f ms.\n\n", size, gpu_elapsed_time_ms);

    //CPU
    cudaEventRecord(start, 0);
    SAXPY(size, alpha, H_X, H_YY);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&cpu_elapsed_time_ms, start, stop);
    printf("Time elapsed on saxpy of %ld on CPU: %f ms.\n\n", size, cpu_elapsed_time_ms);

    cudaFree(D_X);
    cudaFree(D_Y);
    cudaFreeHost(H_Y);
    cudaFreeHost(H_YY);
    cudaFreeHost(H_X);
    return 0;
}

/*
 * SAXPY Function R = aX + Y
 * @param size the lenght of the vectors
 * @param alpha the const to scale the vector X
 * @param X a vector of floats
 * @param Y a vector of floats
 */
void SAXPY(long size, float alpha, float *X, float *Y)
{
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
void generateFloatVector(float *vector, long size)
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
 * Function that copy a vector
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)dest the place where the data will be stored. 
 * @param (OUTPUT)src the place where the data will be stored.  
 */
void copyVector(float *dest, float *src, long size)
{   
    long i;
    #ifdef PARALLEL
    #pragma omp parallel for  private(i) shared(size, vector)
    #endif
    for(i=0; i<size;i++){
        dest[i] = src[i];
    }
}

/*
 * Function that prints a vector on screen
 * @param (INPUT)size the length of the vector
 * @param (INPUT)vector the place where the data will be stored. 
 */
void printIntVector(float *vector, long size)
{   
    printf("[");
    for(long i=0; i<size;i++){
        printf(" %f ", vector[i]);
    }
    printf("]\n");
}