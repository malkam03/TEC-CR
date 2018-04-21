# Workshop 2
Third assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use of SSE.

## Prerequisites
The assignment can be downloaded and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.     
***GCC compiler***    
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install gcc
```

## Running

To compile the programs just type make on a terminal to build them all:
```
make
```
Or if you want to compile just one of the programs type:
```
make target
```
The targets can be:
* **hello:** example hello_simd.c file provided by the professor
* **max:** Vectors data maxes
* **saxpy_ser:** SAXPY function Serial

To run it with the default values type on a terminal:
```
./target 
```
The programs accepts command line options to configure some variables:
```
./max v1.1 v1.2 ... v1.8 v2.1 v2.2 ... v2.8 [vn.1 ... vn.8]
./matMult v1.1.1 v1.1.2 ... v1.1.4 ... v1.2.1 v1.2.2 ... v1.2.4 ... v2.4.1 v2.4.2 ... v2.4.4 
```
For simplicity the program will accept just n positional arguments.
## Author
* **Malcolm Davis** - *Initial work* 

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md).
