# Project 1 Image Cipher APP
First project of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use and comunication of two processors a given Cortex A9 and our own implemantation of a vectorial processor. This app will divide the load of cipher an image between the two processors.

## Prerequisites
The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.     
***GCC compiler***    
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install gcc
```

***OpenCV***    
Opencv is used for image operations, so you should install it to compile the project. You can find the installation instructions on the official [webpage](https://www.learnopencv.com/install-opencv3-on-ubuntu/).


## Running

To compile the program just type make on a terminal:
```
make
```
To run it type on a terminal:
```
./cipher -[x|d|c|a] value -f filePath -s* saveFilePath -m* [main processor load] 
```
Arguments with a '*' are optional, defaults will be used in case the user don't provide one(or in case of the s the program will not save the image). 
* **x** for xor with value 'string with key eg. 10011001',
* **d** for shift(simple) with value 'shamt -7 up to 7'
* **c** for circular shift with value 'shamt -7 up to 7'.
* **a** for add with value 'space separated 0-255 ints',
* **f** to load a file with the file path as the value,
* **s** to save the ciphered image with the save path as the value,
* **m** for the main processor load with a int 0-100 as the value.     

## Author
* **Malcolm Davis** - *Initial work* 

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
