// Processing Kernel
__kernel void saxpy(__global const int *Y, __global const int *X, __global const int *R, __global int a, ) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
    R[i] = a*X[i] + Y[i];
}
