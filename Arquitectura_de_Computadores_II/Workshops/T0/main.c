/* 
 * File:   main.c
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on Feb 16, 2018
 * Simple N even number of threads pair communication in C with pthreads
 *
 * Ussage: 
 * ./argv[0] for default parameters or;
 * ./argv[0] <runing time from 1 to 10> <max array size from 1 to 100> <sampling time> <printing samples time> <number of threads even number>
 */

#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h> 
#include <limits.h>

#define MAX_SIZE 100 			// Array size
#define SAMPLING_TIME 10000 	// In Micro Seconds
#define MAX_RUNING_TIME 10 		// In Seconds
#define PRINT_SAMPLE_TIME 10000 // In Micro Seconds
#define NUMBER_OF_THREADS 2		// 1 Generator and 1 Printer

void* generateCharArray(void * args);
void* printCharArray(void * args);

struct arg_struct {
	unsigned char* array;
	char stop;
	int pos;
	int maxSize;
	int samplingTime;
	int printingTime;
	int threadID;
	pthread_mutex_t mutex;
};

/*
 * Main method, retrive command line options, create the threads
 */
int main(int argc, char const *argv[])
{
	//Retrive command line options
	int runTime, returnCode, arraySize, samplingTime, printingTime, numberOfThreads;
	runTime = argc >= 2 &&  atoi(argv[1]) > 0 && atoi(argv[1]) < MAX_RUNING_TIME ?  atoi(argv[1]) : MAX_RUNING_TIME;
	arraySize = argc >= 3 && atoi(argv[2]) > 0 && atoi(argv[2]) < MAX_SIZE  ?   atoi(argv[2]) : MAX_SIZE;
	samplingTime = argc >= 4 && atoi(argv[3]) > 0 ?  atoi(argv[3]) : SAMPLING_TIME;
	printingTime = argc >= 5 && atoi(argv[4]) > 0 ? atoi(argv[4]) : PRINT_SAMPLE_TIME;
	numberOfThreads = argc >= 6 && atoi(argv[5]) > 0 && atoi(argv[5]) % 2 == 0 ? atoi(argv[5]) : NUMBER_OF_THREADS;

	// Allocate memory for threads and their functions arguments
	pthread_t* threads = (pthread_t*)malloc(numberOfThreads*sizeof(pthread_t));
	struct arg_struct*  args =(struct arg_struct*)malloc((numberOfThreads/2)*sizeof(struct arg_struct));


	srand(time(NULL));
	// Initializes the data for the arguments and start the threads
	for (int threadNo = 0; threadNo < numberOfThreads; threadNo+=2){
		args[threadNo/2+threadNo%2].stop = 0;
		args[threadNo/2+threadNo%2].array = (unsigned char*)malloc(MAX_SIZE*sizeof(unsigned char));
		args[threadNo/2+threadNo%2].pos = 0;
		args[threadNo/2+threadNo%2].maxSize = arraySize;
		args[threadNo/2+threadNo%2].samplingTime = samplingTime;
		args[threadNo/2+threadNo%2].printingTime = printingTime;
		args[threadNo/2+threadNo%2].threadID = threadNo;
		pthread_mutex_init(&args[threadNo/2+threadNo%2].mutex, NULL);

		if( (returnCode=pthread_create( &threads[threadNo], NULL, &generateCharArray, (void *)&args[threadNo/2+threadNo%2])) )
			printf("Thread creation failed: %d\n", returnCode);
		if( (returnCode=pthread_create( &threads[threadNo+1], NULL, &printCharArray, (void *)&args[threadNo/2+threadNo%2])) )
			printf("Thread creation failed: %d\n", returnCode);
	}
		
	// Do the thread work for "runTime" seconds
	sleep(runTime);
	// Change the stop flag 
	for (int threadNo = 0; threadNo < numberOfThreads; threadNo+=2){
		args[threadNo/2+threadNo%2].stop = 1;
	}

	// Wait till threads are done and then free the array memory of that pair of threads
	for (int threadNo = 0; threadNo < numberOfThreads; threadNo+=2){
		pthread_join( threads[threadNo], NULL);
		pthread_join( threads[threadNo+1], NULL);
		free(args[threadNo/2+threadNo%2].array);
	}

	// Free the memory of the threads and args
	free(threads);
	free(args);
	printf("\nCreated samples in a array with size %d for a time of %d seconds with a sampling time of %d micro seconds and pringting \
time of %d micro seconds over %d threads.\nThis values can be modified by calling %s <runing time from 1 to 10> <max array size from 1 to 100> <samplin\
g time> <printing samples time> <number of threads even number>.\n", arraySize, runTime, samplingTime, printingTime, numberOfThreads, argv[0]);
	exit(EXIT_SUCCESS);
}

/*
 * Function that samples values into a char array until the stop flag is turned on 
 * Uses mutex to safety share the memory array between two threads
 * @param args is a void pointer expecting a struct arg_struct data type 
 */
void* generateCharArray(void * args){
	struct arg_struct * threadArgs = (struct arg_struct *)args;
	while(!threadArgs->stop){
		pthread_mutex_lock( &threadArgs->mutex );
		threadArgs->array[threadArgs->pos++] = (char)(rand()%255);
		printf("***The number %d was generated on thread %d.****\n", threadArgs->array[threadArgs->pos-1], threadArgs->threadID);
		if(threadArgs->pos >= threadArgs->maxSize) {
			threadArgs->pos = 0;
			printf("Array on thread %d flushed.\n", threadArgs->threadID);
		}
		pthread_mutex_unlock( &threadArgs->mutex );
		usleep(threadArgs->samplingTime);
	}
}

/*
 * Function that prints the samples until the stop flag is turned on
 * Uses mutex to safety share the memory array between two threads
 * @param args is a void pointer expecting a struct arg_struct data type 
 */
void* printCharArray(void * args){
	struct arg_struct * threadArgs = (struct arg_struct *)args;
	while(!threadArgs->stop){
		pthread_mutex_lock( &threadArgs->mutex );
		printf("Array [");
		for(int i =0; i<threadArgs->pos; i++)
			printf(" %d ", threadArgs->array[i]^0x20);
		printf("] on thread %d.\n", threadArgs->threadID+1);
		pthread_mutex_unlock( &threadArgs->mutex );
		usleep(threadArgs->printingTime);
	}
}