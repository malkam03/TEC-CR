/* 
 * File:   mpiImageFilter.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on May 8, 2018
 * Image filter in a heterogeneous cluster via mpi
 * This program applies a 
 * filter to each pixel in a image.
 * This code is intended to be exemplify the use of mpi in a small cluster to filter a image
 *
 * Ussage: 
 * ./mpiImageFilter filePath
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *
 */
void filter();


/*
 *
 */
typedef struct Image{
	int nRows;
	int nCols;
	unsigned char* Data;
	unsigned char Type;
} Image;


/*
 *
 */
int main(int argc, char * argv[]){
	//Get the Image Name and path
	if (argc != 2){
		printf("Invalid entry.\n Ussage: \t%s imagePath\n", argv[0]);
		return -1;
	}
	int nRows=640,
		nCols=480,
		rank,
		nRanks,
		i, j;
	MPI_File image;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nRanks);

	Image subImage =  {
		.nRows = nRows/nRanks,
		.nCols = nCols/nRanks,
		.Type = 0
	};
	subImage.nRows +=  rank > nRows%nRanks ? 0 : 1;
	subImage.nCols +=  rank > nCols%nRanks ? 0 : 1;
	subImage.Data = malloc(subImage.nRows*subImage.nCols*sizeof(char));
	if(MPI_File_open(MPI_COMM_WORLD, argv[1], MPI_MODE_RDWR, MPI_INFO_NULL, &image)){
		if (rank==0) fprintf(stderr, "No valid file %s.\n", argv[1]);
		MPI_Abort( MPI_COMM_WORLD, 1 );
		return -1;
	}

	
	printf("Runing this from rank %d of %d.\n My data is %d by %d image %s.\n", rank, nRanks, subImage.nRows, subImage.nCols, argv[1]);
	MPI_Finalize();

	return 0;
}