# Workshop 0
First assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use of pthreads.

## Prerequisites
The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter(pthreads in windows are possible but a little tricky).     
***GCC compiler***    
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install gcc
```

## Running

To compile the program just type make on a terminal:
```
make
```
To run it with the default values type on a terminal:
```
./run 
```
The program accepts command line options to configure some variables:
```
./run <runing time from 1 to 10> <max array size from 1 to 100> <sampling time> <printing samples time> <number of threads even number>
```
For simplicity the program will accept just n positional arguments.
## Author
* **Malcolm Davis** - *Initial work* 

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
