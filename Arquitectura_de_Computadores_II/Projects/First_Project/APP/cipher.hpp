/* 
 * File:   cipher.hpp
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
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cctype>
#include <string>

//Constant definitions
#define XOR 0
#define ADD 1
#define SIMPLE_SHIFT 2
#define CIRCULAR_SHIFT 3
#define MAIN_CPU_COMPUTE_DEFAULT 50

//Function definitions
/* Help function, prints on standard output the ussage of this program.
 * @param name the name of the compiled file
 */
void help(char * name);


/*
 * Xor function to cipher a Image
 * @param start pointer to the first pixel to cipher
 * @param end pointer to the last pixel to cipher
 * @param key a unsigned char with the key to make the bitwise xor operation
 */
void xorCiph(const uchar* start, const uchar* end, uchar key);


/*
 * Add function to cipher a Image
 * @param start pointer to the first pixel to cipher
 * @param end pointer to the last pixel to cipher
 * @param keys a unsigned list of chars with the key to make the add operation
 * @param size the size of the memory array with keys
 */
void addCiph(const uchar* start, const uchar* end, uchar * keys, int size);


/*
 * Simple shift function to cipher a Image
 * @param start pointer to the first pixel to cipher
 * @param end pointer to the last pixel to cipher
 * @param shampt shift amount (positive right negative left 0-7)
 */
void sShiftCiph(const uchar* start, const uchar* end, short shamt);


/*
 * Circular shift function to cipher a Image
 * @param start pointer to the first pixel to cipher
 * @param end pointer to the last pixel to cipher
 * @param shampt shift amount (positive right negative left 0-7)
 */
void cShiftCiph(const uchar* start, const uchar* end, short shamt);

/*
 * Gets a list of uchars from a string with space separated numbers
 * @param data string with space separated 0-255 numbers
 * @param list the return array with uschars
 * @oaram size the return size of the array
 */
void ucharList(char* data, uchar* array, int *size);