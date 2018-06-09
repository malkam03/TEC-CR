NVCC = nvcc

all: matrixMult

%.o : %.cu
	$(NVCC) -DPARALLEL -c $< -o $@

matrixMult : matrixMult.o
	$(NVCC) $^ -o $@

clean:
	rm -rf *.o *.a matrixMult
