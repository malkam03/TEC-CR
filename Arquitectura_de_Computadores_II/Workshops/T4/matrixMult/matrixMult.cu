/* 
 * File:   matrixMult.cu
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on May 9, 2018
 * Simple Matrix Multiplication with CUDA
 * Based on https://github.com/lzhengchun/matrix-cuda
 * Ussage: 
 * ./argv[0] for default parameters and random vectors or;
 * ./argv[0] <matrix 1 n size> <matrix 1 m size(and matrix 2 n size)> <matrix 2 m size>
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INT_RAND_MAX 10000
#define BLOCK_SIZE 16
#define MATRIX_SIZE_N 4
#define MATRIX_SIZE_M 4
#define MATRIX_SIZE_P 4

typedef struct intMatrix{
  int * data;
  long nrows;
  long ncols;
} intMatrix;

void generateMatrix(struct intMatrix* mat);
void printMatrix(struct intMatrix* mat);
void matMult(struct intMatrix* A, struct intMatrix* B, struct intMatrix* C);


/*
 *GPU KERNEL
 */
__global__
void cudaMult(int *a, int *b, int *c, int m, int n, int p)
{ 
    int row = blockIdx.y * blockDim.y + threadIdx.y; 
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int sum = 0;
    if( col < p && row < m) 
    {
        for(int i = 0; i < n; i++) 
        {
            sum += a[row * n + i] * b[i * p + col];
        }
        c[row * p + col] = sum;
    }
} 


/*
 * Main method, retrive command line options, create the threads
 */
int main(int argc, char const *argv[])
{
    const int printMatrixB = getenv("PRINT_MATRIX") ? 1 : 0;
    srand(time(NULL));
    // If the vector size is inserted then use it if not then use the default 
    long m = argc > 1 && atol(argv[1]) > 0 ? atol(argv[1]) : MATRIX_SIZE_M;
    long n = argc > 2 && atol(argv[2]) > 0 ? atol(argv[2]) : MATRIX_SIZE_N;
    long p = argc > 3 && atol(argv[3]) > 0 ? atol(argv[3]) : MATRIX_SIZE_P;

    // Allocate memory for the Matrix
    struct intMatrix H_A, H_B, H_C, H_CC;
    H_A.nrows = m;
    H_A.ncols = n;
    H_B.nrows = n;
    H_B.ncols = p;
    H_C.nrows = m;
    H_C.ncols = p;
    H_CC.nrows = m;
    H_CC.ncols = p;
    cudaMallocHost((void **) &H_A.data, sizeof(int)*m*n);
    cudaMallocHost((void **) &H_B.data, sizeof(int)*n*p);
    cudaMallocHost((void **) &H_C.data, sizeof(int)*m*p);
    cudaMallocHost((void **) &H_CC.data, sizeof(int)*m*p);
    
    // Generate random Matrix
    generateMatrix(&H_A);
    generateMatrix(&H_B);

    float gpu_elapsed_time_ms, cpu_elapsed_time_ms;

    // some events to count the execution time
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // start to count execution time of GPU version
    cudaEventRecord(start, 0);
    // Allocate memory space on the device 
    int* D_A, *D_B, *D_C;
    cudaMalloc((void **) &D_A, sizeof(int)*m*n);
    cudaMalloc((void **) &D_B, sizeof(int)*n*p);
    cudaMalloc((void **) &D_C, sizeof(int)*m*p);

    // copy matrix A and B from host to device memory
    cudaMemcpy(D_A, H_A.data, sizeof(int)*m*n, cudaMemcpyHostToDevice);
    cudaMemcpy(D_B, H_B.data, sizeof(int)*n*p, cudaMemcpyHostToDevice);

    unsigned int grid_rows = (m + BLOCK_SIZE - 1) / BLOCK_SIZE;
    unsigned int grid_cols = (p + BLOCK_SIZE - 1) / BLOCK_SIZE;
    dim3 dimGrid(grid_cols, grid_rows);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);

    // Launch kernel
    cudaMult<<<dimGrid, dimBlock>>>(D_A, D_B, D_C, m, n, p);
    // Transefr results from device to host 
    cudaMemcpy(H_C.data, D_C, sizeof(int)*m*p, cudaMemcpyDeviceToHost);
    cudaThreadSynchronize();
    // time counting terminate
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    // compute time elapse on GPU computing
    cudaEventElapsedTime(&gpu_elapsed_time_ms, start, stop);
    printf("Time elapsed on matrix multiplication of %ldx%ld . %ldx%ld on GPU: %f ms.\n\n", m, n, n, p, gpu_elapsed_time_ms);

    // start the CPU version
    cudaEventRecord(start, 0);

    matMult(&H_A, &H_B, &H_CC);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&cpu_elapsed_time_ms, start, stop);
    printf("Time elapsed on matrix multiplication of %ldx%ld . %ldx%ld on CPU: %f ms.\n\n", m, n, n, p, cpu_elapsed_time_ms);

    // validate results computed by GPU
    int all_ok = 1;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < p; ++j)
        {
            if(H_C.data[i*p + j] != H_CC.data[i*p + j])
            {
                all_ok = 0;
            }
        }
    }

    // roughly compute speedup
    if(all_ok)
    {
        printf("all results are correct!!!, speedup = %f\n", cpu_elapsed_time_ms / gpu_elapsed_time_ms);
    }
    else
    {
        printf("incorrect results\n");
    }

    // free memory
    cudaFree(D_A);
    cudaFree(D_B);
    cudaFree(D_C);
    cudaFreeHost(H_A.data);
    cudaFreeHost(H_B.data);
    cudaFreeHost(H_C.data);
    cudaFreeHost(H_CC.data);
    return 0;
}


/*
 * matMult Function C = A*B
 * @param C the return matrix
 * @param A a matrix of ints
 * @param B a matrix of ints
 */
void matMult(struct intMatrix* A, struct intMatrix* B, struct intMatrix* C){
  long i, j, k;
  double sum = 0;
  #ifdef PARALLEL
  #pragma omp parallel for private(i,j,k, sum) shared(A, B, C)
  #endif
  for (i = 0; i < A->nrows; i++) {
      for (j = 0; j < B->ncols; j++) {
        for (k = 0; k < B->nrows; k++) {
          sum = sum + A->data[i*A->nrows+k]*B->data[k*B->nrows+j];
        }
        C->data[i*C->nrows+j] = sum;
        sum = 0;
      }
    }
}


/*
 * Function that fills a vector of size "size" with random numbers
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)vector the place where the data will be stored.  
 */
void generateMatrix(struct intMatrix* matrix){
  long i, j;
  #ifdef PARALLEL
  #pragma omp parallel for private(i, j) shared(matrix)
  #endif
  for(i=0; i < matrix->nrows; i++){
    for(j=0; j < matrix->ncols; j++){
      matrix->data[i*matrix->nrows+j] = (int16_t)ceil(((double)rand()/(double)(RAND_MAX)) * INT_RAND_MAX);
    }
  }
}

/*
 * Function that prints a vector on screen
 * @param (INPUT)size the length of the vector
 * @param (INPUT)vector the place where the data will be stored. 
 */
void printMatrix(struct intMatrix* matrix){
  for(long i=0; i < matrix->nrows; i++){
    printf("[");
    for(long j=0; j < matrix->ncols; j++){
      printf(" %hd ", matrix->data[i*matrix->nrows+j]);
    }
    printf("]\n");
  }
}