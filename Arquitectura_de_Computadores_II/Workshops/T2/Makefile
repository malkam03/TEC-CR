# Declaration of variables
CC = gcc
CC_FLAGS =

# Main Target
all: hello max

# PI approximation serial
hello: hello_simd.o
	$(CC) hello_simd.c  $(CC_FLAGS) -o hello_SSE

max: max_SSE.o
	$(CC) max_SSE.c  $(CC_FLAGS) -o pi_par

saxpy_ser: saxpy.o
	$(CC) saxpy.c  $(CC_FLAGS) -o saxpy_ser

saxpy_par: saxpy.o
	$(CC) saxpy.c -DPARALLEL  $(CC_FLAGS) -o saxpy_par

matmul_ser: matMul.o
	$(CC) matMul.c  $(CC_FLAGS) -o matmul_ser

matmul_par: matMul.o
	$(CC) matMul.c -DPARALLEL  $(CC_FLAGS) -o matmul_par
 
# To remove generated files
clean:
	rm -f pi_ser pi_par saxpy_ser saxpy_par matmul_ser matmul_par *.o 
