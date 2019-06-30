# Tarea 1
First assignment of the course CE-3102 "Análisis Numérico para Ingeniería", second semester 2017. Aims to test some errors related to calculations with simple and double precision.

## Prerequisites
The assignment can be downloaded and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.   
***Octave***
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install octave
```
***C++ Compiler***
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install g++
```
## Running

For the first problem, just open the problema1.m file, located in the directory Problema 1, with octave and run the function with the desired parameters n(number of iterations) and x(the number to add).
For the second and the third problem just open a terminal on the Problema 1 and problema 2 directories respectively and type:
```
make
./run
```
The second and third problem accepts parameters via terminal, if the run file is called without them, it will execute the defaults(see documentation for each problem).
## Author
* **Malcolm Davis** - *Initial work* - [ITCR/Análisis Númerico para la Ingienería/Tarea 1](https://github.com/malkam03/ITCR/tree/Analisis_Numerico_para_la_Ingenieria/Tarea1)

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)


