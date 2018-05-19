# Declaration of variables
CC = mpicc
CC_FLAGS = -std=c++11 `pkg-config --libs --cflags opencv` -lstdc++ -lm

# Main Target
all: ImageFilter_MPI ImageFilter_MPI_OMP


# Image Filter MPI
ImageFilter_MPI: mpiImageFilter.cpp
	$(CC) mpiImageFilter.cpp  $(CC_FLAGS) -o imageFilter_MPI

# Image Filter MPI+openMP
ImageFilter_MPI_OMP: mpiImageFilter.cpp
	$(CC) mpiImageFilter.cpp -DOMP $(CC_FLAGS) -o imageFilter_MPI_OMP
 
# To remove generated files
clean:
	rm -f imageFilter_MPI* *.o 