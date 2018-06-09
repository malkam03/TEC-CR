/* 
 * File:   cipher.cpp
 * Author: Malcolm Davis
 * Course: Computer Architecture II
 * Created on Mar 3, 2018
 * Image filter in a heterogeneous multi processor enviroment
 * This program applies a xor, simple shift, circular shift or add
 * filter to each pixel in a image.
 * This code is intended to be optimized for the Cortex A9 as the main processor and our
 * own implementation of a vectorial processor
 *
 * Ussage: 
 * ./argv[0] -[x|d|c|a] value -f filePath -s* saveFilePath -m* [main processor load]
 * With: x for xor with value 'string with key eg. 10011001',
 * d for shift(simple) with value 'shamt -7 up to 7'
 * c for circular shift with value 'shamt -7 up to 7'.
 * a for add with value 'space separated 0-255 ints',
 * f to load a file with the file path as the value,
 * s to save the ciphered image with the save path as the value,
 * and m for the main processor load with a int 0-100 as the value.
 */
#include "cipher.hpp"

/*
 * Main method, retrive command line options, create the threads
 */
int main(int argc, char ** argv)
{
	char *optValue = NULL;
	char *filePath = NULL;
	char *savePath = NULL;
	int index, optOption, mainComputeP = MAIN_CPU_COMPUTE_DEFAULT;
	short operation;
	//Loop throught command line options inserted, at least a cipher method and filename should be provided
	while ((optOption = getopt (argc, argv, "x:d:c:a:f:s:m:")) != -1){
		if(!optarg){
			help(argv[0]);
			abort();
		}
	    switch (optOption)
	    {
			case 'x':
				printf("Case xor key: %s\n", optarg);
				optValue = optarg;
				operation = XOR;
				break;
			case 'd':
				printf("Case simple shift: %s\n", optarg);
				optValue = optarg;
				operation = SIMPLE_SHIFT;
				break;
			case 'c':
				printf("Case circular shift: %s\n", optarg);
				optValue = optarg;
				operation = CIRCULAR_SHIFT;
				break;
		    case 'a':
				printf("Case add with add vector: %s\n", optarg);
		    	optValue = optarg;
				operation = ADD;
				break;
		    case 'f':
				printf("File path provided: %s\n", optarg);
		    	filePath = optarg;
				break;
		    case 's':
				printf("Save file path provided: %s\n", optarg);
		    	savePath = optarg;
				break;
		    case 'm':
		    	mainComputeP = (atoi(optarg) >= 0 && atoi(optarg) <=100 ) ? atoi(optarg) : MAIN_CPU_COMPUTE_DEFAULT;
				printf("Main Processor Load: %d Vector Processor Load: %d\n", mainComputeP, 100-mainComputeP);
				break;
			case '?':
				if (std::isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else{
					fprintf (stderr,
					         "Unknown option character `\\x%x'.\n",
				              optopt);
					help(argv[0]);
				}
				abort();
			default:
				help(argv[0]);
				abort();
	    }
	}
	if (optValue and filePath){
		cv::Mat ciphered, original = cv::imread(filePath, CV_LOAD_IMAGE_COLOR);
		cv::cvtColor(original, ciphered, cv::COLOR_BGR2GRAY);
		// Split the data load
		// Main CPU
		const uchar* mainDataStart = ciphered.datastart;
		const uchar* mainDataEnd = ciphered.datastart + sizeof(uchar)*((ciphered.rows*ciphered.cols*mainComputeP)/100);
		// Vector CPU
		const uchar* secDataStart = ciphered.datastart + sizeof(uchar)*(((ciphered.rows*ciphered.cols)*mainComputeP/100)+1);
		const uchar* secDataEnd = ciphered.dataend;
		//Process stuff
		int size;
		uchar* keys;
		switch (operation){
			case XOR:
				xorCiph(mainDataStart, mainDataEnd, (uchar)std::stoi(optValue, nullptr, 2)%255);
				break;
			case ADD:
				size =0;
				keys = (uchar*) malloc((strlen(optValue)/2)*sizeof(uchar));
				ucharList(optValue, keys, &size);
				addCiph(mainDataStart, mainDataEnd, keys, size);
				free(keys);
				break;
			case SIMPLE_SHIFT:
				sShiftCiph(mainDataStart, mainDataEnd, atoi(optValue));
				break;
			case CIRCULAR_SHIFT:
				cShiftCiph(mainDataStart, mainDataEnd, atoi(optValue));
				break;
			default:
				help(argv[0]);
				abort();

		}
		cv::imshow("Original", original);
		cv::imshow("Ciphered", ciphered);
		if(savePath)
			cv::imwrite(savePath, ciphered );
		cv::waitKey(0);
	}else{
		help(argv[0]);
		abort();
	}
	return 0;
}


void help(char *name){
	fprintf(stderr, "Usage: '%s -[x|d|c|a] value -f filePath',\n\
With: x option for xor with value 'space separated 0-255 ints',\n\
d for shift(simple) with value 'shamt -7 up to 7'\n\
c for circular shift with value 'shamt -7 up to 7'.\n\
and a for add with value 'space separated 0-255 ints'\n\
f for load a file with the file path as the value,\n\
s for save the ciphered image with the save path as the value,\
m for the main processor load with a int 0-100 as the value.\n", name);
}


void ucharList(char* data, uchar* array, int *size){
	char * number;
	*size =0;
	number = strtok (data," ");
	while (number != NULL)
	{
		array[(*size)++]=(uchar)atoi(number);
		number = strtok (NULL, " ");
	}
}


void xorCiph(const uchar* start, const uchar* end, uchar key){
	for (uchar * pixel = const_cast<uchar*>(start); pixel <= end; ++pixel){
		*pixel=*pixel ^ key;
	}
}

void addCiph(const uchar* start, const uchar* end, uchar * keys, int size){
	if((start-end)%size!=0){
		fprintf(stderr, "No valid add vector, has to be a multiple of the data to process.");
		abort();
	}
	for (uchar * pixel = const_cast<uchar*>(start); pixel <= end; pixel+=1){
		for(int i=0; i<size; i++){
			*pixel=(uchar)std::min(*(pixel + i)+*(keys+i), 255);
		}
	}
}

void sShiftCiph(const uchar* start, const uchar* end, short shamt){
	if (shamt >0)
		for (uchar * pixel = const_cast<uchar*>(start); pixel <= end; ++pixel){
			*pixel=*pixel >> shamt;
		}
	else{
		shamt *=-1;
		for (uchar * pixel = const_cast<uchar*>(start); pixel <= end; ++pixel){
			*pixel=*pixel << shamt;
		}
	}
}

void cShiftCiph(const uchar* start, const uchar* end, short shamt){
	if (shamt >0)
		for (uchar * pixel = const_cast<uchar*>(start); pixel <= end; ++pixel){
			*pixel=(*pixel >> shamt) | (*pixel << (8-shamt));
		}
	else{
		shamt *=-1;
		for (uchar * pixel = const_cast<uchar*>(start); pixel <= end; ++pixel){
			*pixel=(*pixel << shamt) | (*pixel >> (8-shamt));
		}
	}
}