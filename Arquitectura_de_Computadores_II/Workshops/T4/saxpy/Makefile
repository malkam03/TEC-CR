NVCC = nvcc

all: saxpy

%.o : %.cu
	$(NVCC) -DPARALLEL -c $< -o $@

saxpy : saxpy.o
	$(NVCC) $^ -o $@

clean:
	rm -rf *.o *.a saxpy
