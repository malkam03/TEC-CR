/* 
 * File:   mpiImageFilter.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on May 8, 2018
 * Image filter in a heterogeneous cluster via mpi
 * This program applies a 
 * filter to each pixel in a image.
 * This code is intended to be exemplify the use of mpi in a small cluster to filter a image with adding Rayleigh Noise
 *
 * Ussage: 
 * ./mpiImageFilter filePath variance
 */
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_VAR 600

void rayleighNoise(const uchar* start, int size, int var);


/*
 * Main gets arguments and runs the filter
 */
int main(int argc, char * argv[]){
	//Get the Image Name and path
	if (argc < 2 || argc >3){
		printf("Invalid entry.\n Ussage: \t%s imagePath variance\n", argv[0]);
		return -1;
	}
	const int showImages = getenv("SHOW_IMAGES") ? 0 : 1;
	int rank,nRanks, nameLen, 
		var = argc > 2 && atol(argv[2]) > 0 ? atol(argv[2]) : DEFAULT_VAR;
	double startTime, runTime;
	char hostName[MPI_MAX_PROCESSOR_NAME];
	srand((time(NULL)));
	long nPixels;
	cv::Mat original, filtered;
	//Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nRanks);
	MPI_Get_processor_name(hostName, &nameLen);

	//The main rank calculates the data to send to other ranks
	if(rank == 0){
		original = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
		if(original.data==NULL){
			fprintf(stderr,"Cannot open the image %s.\n", argv[1]);
			MPI_Abort(MPI_COMM_WORLD, -1);
		}
		if ((original.rows*original.cols)%nRanks!=0){
			fprintf(stderr,"The image size must be divisible by the number of processes; %d is not divisible by %d.\n", original.cols*original.rows, nRanks);
			MPI_Abort(MPI_COMM_WORLD, -1);
		}
		nPixels = (original.rows*original.cols)/nRanks;
		filtered = cv::Mat(original.rows, original.cols, original.type());
		if(showImages)
			cv::imshow("Original", original);
		startTime = MPI_Wtime();
	}
	//Send to the other ranks the size of the problem
	MPI_Bcast(&nPixels, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	//Waits for all processes to have the total size
	MPI_Barrier(MPI_COMM_WORLD);
	
	//Allocate space for my part of the image
	uchar* data = (uchar *) malloc(nPixels*sizeof(uchar));
	//The rank 0 sends the data of the image to other ranks
	MPI_Scatter(original.data, nPixels, MPI_UNSIGNED_CHAR, data, nPixels, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	//Apply the NOISE in each rank
	rayleighNoise(data, nPixels, var);
	//The rank 0 recieves all the data of the image from other ranks
	MPI_Gather(data, nPixels, MPI_UNSIGNED_CHAR, filtered.data, nPixels, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	printf("%ld pixels filtered on rank %d of %d in host %s.\n", nPixels, rank, nRanks, hostName);
	if(rank==0){
		runTime = MPI_Wtime()-startTime;
		if(showImages)
			cv::imshow("Filtered", filtered);
		cv::waitKey(0);
		#ifdef OMP
		printf("Using OpenMP\n");
		#endif
		printf("Filtered image %s with %d ranks took %f s.\n", argv[1], nRanks, runTime);
	}
	

	MPI_Finalize();
	//cv::imshow("Original", original);
	free(data);
	return 0;
}

/*
 * Rayleigh filter implementation
 * @param start start of the uchar array
 * @param size the size of the uchar array
 * @param var the variance of the noise
 */
void rayleighNoise(const uchar* start, int size, int var){
	uchar * pixel;
	float NOISE, A;
	#ifdef OMP
	#pragma omp parallel for private(pixel) shared(start)
	#endif
	for (pixel = const_cast<uchar*>(start); pixel <= (start+size); ++pixel){
		A=2.3299*var;
		NOISE=sqrt(-2*A*log(1.0-(float)rand()/RAND_MAX));
		if(NOISE>255)
			NOISE=255;
		if(NOISE<0)
			NOISE=0;
		*pixel+=(uchar)(NOISE+.5);
	}
};