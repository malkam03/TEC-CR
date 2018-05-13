# Workshop 1
Second assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use of OpenMP.

## Prerequisites
The assignment can be downloaded and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.     
***GCC compiler***    
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install gcc
```
***Python TK***    
If you wish to use the script to plot serial data then you must have python Tk installed, you can install it with:
```
sudo apt install python3-tk
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
* **pi_ser:** Pi aproximation Serial
* **pi_par:** Pi aproximation Parallel
* **saxpy_ser:** SAXPY function Serial
* **saxpy_par:** SAXPY function Parallel
* **matMul_ser:** Matrix Multiplication function Serial
* **matMul_par:** Matrix Multiplication function Parallel

After building the files you can plot test data with one of the plot scripts:
```
./piPlotScript.sh
./saxpyPlotScript.sh
./matMulPlotScript.sh
```

To run it with the default values type on a terminal:
```
./target 
```
The program accepts command line options to configure some variables:
```
./target size 
```
The size in almost all the targets is one positive integer that represent the steps for pi, the size of the vectors for the saxpy. But the matrix multiplication program will accept 4 sizes representing the mxn sizes of matrix A and B. **The sizes of the matrixes have to be compatible with the multiplication formula.**
For simplicity the program will accept just n positional arguments.
## Author
* **Malcolm Davis** - *Initial work* 

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md).
