/* 
 * File:   main.c
 * Author: Malcolm Davis
 * Created on Feb 16, 2018
 * Simple two thread communication in C with pthreads
 */

#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 100

/*
 */
void generateCharArray(unsigned char* array, int pos){
	array[pos] = (char)(rand()%255);
	printf("Se generó el número: %d, o en char: %c.\n", array[pos], array[pos]);
}

int main(int argc, char const *argv[])
{
	int maxSize = MAXSIZE;
	pthread_t generator;
	pthread_t printer;

	unsigned char * array = (unsigned char*)malloc(maxSize*sizeof(unsigned char));
	srand(time(NULL));
	for(int i=0; i<maxSize; i++){
		generateCharArray(array, i);
	}

	return 0;
}

