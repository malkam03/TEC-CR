/* 
 * File:   saxpy.cu
 * Author: Don't Know but Malcolm Davis Modify it
 * Course: Computer Architecture II
 * Created on May 23, 2018
 * Simple SAXPY(Single-precision Alpha*X Plus Y) operation with OpenCL
 * Modified the hello.c example provided
 *
 * Ussage: 
 * ./argv[0] for default parameters and random vectors or;
 * ./argv[0] <array size>
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Include OpenCL headers 
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
// What's up with this? :O
#define MAX_SOURCE_SIZE (0x100000)
#define INT_RAND_MAX 100000
 
/*
 * Function that fills a vector of size "size" with random numbers
 * @param (INPUT)size the length of the vector
 * @param (OUTPUT)vector the place where the data will be stored.  
 */
void generateIntVector(int *vector, long size)
{   
    long i;
    #ifdef PARALLEL
    #pragma omp parallel for  private(i) shared(size, vector)
    #endif
    for(i=0; i<size;i++){
        vector[i] = ((float)rand()/(float)(RAND_MAX)) * INT_RAND_MAX;
    }
}

int main(int argc, char** argv) {
    // Create the two input vectors
    int i, a;
    srand(time(NULL));
    const int LIST_SIZE = argc > 1 && atol(argv[1]) > 0 ? atol(argv[1]) : 1024;
    int *X = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *Y = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
    generateIntVector(X, LIST_SIZE);
    generateIntVector(Y, LIST_SIZE);
    a = ((float)rand()/(float)(RAND_MAX)) * INT_RAND_MAX;
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
    // Read the kernel
    fp = fopen("saxpy.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
 
    //1. Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
#ifdef GPU
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, 
            &device_id, &ret_num_devices);
#else
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_CPU, 1, 
            &device_id, &ret_num_devices);
#endif
 
    //2. Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
 
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 
    // Create memory buffers on the device for each vector 
    cl_mem y_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem x_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
            LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            sizeof(int), NULL, &ret);
 
    // Copy the lists Y and X to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, y_mem_obj, CL_TRUE, 0,
            LIST_SIZE * sizeof(int), Y, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, x_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), X, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, 
            sizeof(int), &a, 0, NULL, NULL);
 
    //3. Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);
 
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
 
    //4. Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "saxpy", &ret);
 
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&y_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&x_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&a_mem_obj);
 
    //5. Execute the OpenCL kernel on the list
    size_t global_item_size = LIST_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Divide work items into groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
 
    // Read the memory buffer Y1 on the device to the local variable Y1
    int *Y1 = (int*)malloc(sizeof(int)*LIST_SIZE);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, 
            LIST_SIZE * sizeof(int), Y1, 0, NULL, NULL);
 
    // Display the result to the screen
    for(i = 0; i < LIST_SIZE; i++)
        //printf("%d*%d + %d = %d\n", a, Y[i], X[i], Y1[i]);
 
    //6. Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(y_mem_obj);
    ret = clReleaseMemObject(x_mem_obj);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(Y);
    free(X);
    free(C);
    // Be nice
    printf("Hola mundo desde OpenCL+SAXPY\n");
    return 0;
}
