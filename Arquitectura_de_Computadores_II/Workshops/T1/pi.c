/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				 
History: Written by Tim Mattson, 11/99.

#-----------------------------------------------------

Modified by JGG 

#--------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
int main (int argc, char ** argv)
{
	int i, nprocs;
	double x, pi, sum = 0.0;
	double start_time, run_time;
	long number_of_steps = argc >=2 &&  atol(argv[1]) > 0 ? atol(argv[1]) : num_steps;
	step = 1.0/(double) number_of_steps;

	/*start timer */
	start_time = omp_get_wtime();


	for (i=1;i<= number_of_steps; i++){
	x = (i-0.5)*step;
	sum = sum + 4.0/(1.0+x*x);
	}
	
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	if(argc>1)
		printf("Steps: %ld Seconds: %f ", number_of_steps, run_time);
	printf("\n pi is %f in %f seconds \n",pi,run_time);
	
}	  


