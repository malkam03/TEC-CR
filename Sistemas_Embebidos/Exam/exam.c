/*************************************************************************************************  
 *  Este código se utiliza como modelo de comportamiento del sistema embebido a diseñar.         *
 *  La implemetación del código sólo representa la esencia de los procesos y su naturaleza.      *
 *  Éste código puede presentar errores funcionales, de sintaxis y semántica.                    *
 *  Utilizar sólo como una referencia para modelar el sistema. NO trate de compilar el código,   *
 *  ni de analizar la funcionalidad de los procesos. Asuma que el código funciona tal cual está. *
 *  JGG - 2018.                                                                                  *
 *************************************************************************************************/


#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define BUFF_SIZE 1024


// Memory allocation for global buffers
float * raw_data = (float*)malloc(BUFF_SIZE * sizeof(float));
float * filtered_data = (float*)malloc(BUFF_SIZE * sizeof(float));
complex<float> * freq_data = (complex<float>*)malloc(2*BUFF_SIZE * sizeof(complex<float>));
float * power_data = (float*)malloc(BUFF_SIZE * sizeof(float));

//P1- ADC read thread
void *ADC_samples(void *adc_address_ptr) {
	while (1) {
		for (int i = 0;i < BUFF_SIZE, i++){
			//read ADC device
			raw_data[i] = readADC(*adc_address_ptr);
			//100ms sample rate
			sleep(100); 
		}
	}
	return NULL;
}
//P2 - Digital filter
void *Digital_filter(void *filter_size_ptr ){
	while(1){
		for (int i = 0; i < BUFF_SIZE - filter_size_ptr, i++){
			//apply low pass filter
			for (int j = i; j < *filter_size_ptr; j++){
				filtered_data[i] += raw_data[j];
			}
			filtered_data[i] /= *filter_size_ptr;		
		}
	}
	return NULL;
} 

//P3 - Discrete Fourier tranform
void *FFT(void* dummy){  
	while(1){
		complex<float> *W;
		W = (complex<float> *)malloc(BUFF_SIZE / 2 * sizeof(complex<float>));
		W[1] = polar(1., -2. * M_PI / BUFF_SIZE);
		W[0] = 1;
		for(int i = 2; i < BUFF_SIZE / 2; i++)
		W[i] = pow(W[1], i);
		int n = 1;
		int a = BUFF_SIZE / 2;
		for(int j = 0; j < log2(BUFF_SIZE); j++) {
			for(int i = 0; i < BUFF_SIZE; i++) {
			  if(!(i & n)) {
			    complex<float> temp = filtered_data[i];
			    complex<float> Temp = W[(i * a) % (n * a)] * filtered_data[i + n];
			    freq_data[i] = temp + Temp;
			    freq_data[i + n] = temp - Temp;
			  }
			}
			n *= 2;
			a = a / 2;
		}

	}
	return NULL;
}
//P4 - Spectral power stimation
void *Power_calc(void * dummy){
	int n = 1;
	int a = BUFF_SIZE / 2;
	for(int i = 0; i < BUFF_SIZE; i++) {
		if(!(i & n)) 
	    	power[i] = sqrt(pow(freq_data[i],2) + pow(freq_data[i+n],2));
	 
	n *= 2;
	a = a / 2;
	}
	return NULL;
}


int main(int argc, char const *argv[]){
	int * filter_size_ptr;
	*filter_size_ptr = 5;
	//Thread creation
	pthread_t P1, P2, P3, P4;
	pthread_create(&P1, NULL, ADC_samples, 0x8000000);
	pthread_create(&P2, NULL, Digital_filter, &filter_size_ptr);
	pthread_create(&P3, NULL, FFT, 0);
	pthread_create(&P4, NULL, Power_calc, 0);
	//Join Threads
	pthread_join(P1, NULL);
	pthread_join(P2, NULL);
	pthread_join(P3, NULL);
	pthread_join(P4, NULL);
	return 0;
}