# Declaration of variables
CC = mpicc
CC_FLAGS = 

# Main Target
all: mpiImageFilter

# PI approximation serial
mpiImageFilter: mpiImageFilter.c
	$(CC) mpiImageFilter.c  $(CC_FLAGS) -o mpiImageFilter
 
# To remove generated files
clean:
	rm -f mpiImageFilter *.o 