# Declaration of variables
CC = gcc
CC_FLAGS = -lm -fopenmp -w -msse4

# Main Target
all: hello max matMult

hello: hello_simd.o
	$(CC) hello_simd.c  $(CC_FLAGS) -o hello

max: max_SSE.o
	$(CC) max_SSE.c  $(CC_FLAGS) -o max

matMult: matMult_SSE.o
	$(CC) matMult_SSE.c  $(CC_FLAGS) -o matMult

 
# To remove generated files
clean:
	rm -f hello max matMult
