# Workshop 2

Second assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use of pthreads.

## Prerequisites

The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter(pthreads in windows are possible but a little tricky).  
***GCC compiler***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt update
sudo apt install gcc
```

## Running

For this workshop the goal is to develop a dynamic library and a static library, in order to create the static library use the following commands:

```bash
gcc -c se_math.c -o se_math.o
ar rv se_math.a se_math.o
ranlib se_math.a
```

To compile a sample program with this library use:

```bash
gcc simple_calculator.c se_math.a -lm -o calculate_static -I$(pwd)
```

In order to create the dynamic library use:

```bash
gcc -c se_math.c -o se_math.o
ld -o se_math.so se_math.o -shared
```

To compile a sample program with this library use:

```bash
gcc -o calculate_dynamic simple_calculator.c -I$(pwd) -L$(pwd) -lse_math -lm
export LD_LIBRARY_PATH=$(pwd)
```

To run it with the default values type on a terminal:

```bash
./calculate_static operand operator operand
./calculate_dynamic operand operator operand
```

## Author

* **Malcolm Davis** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
