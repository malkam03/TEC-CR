# Workshop 4

Third assignment of the course CE-5303 "Introducción a los Sistemas Embebidos", second  semester 2018. Aims to exemplify the use of autoconfig GNU build tools.

## Prerequisites

The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.  
***GCC compiler***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt update
sudo apt install gcc
```

***Automake***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt-get install automake
```

***Libtool***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt-get install libtool
```

## Running

For this workshop the goal is to compile the previously created dynamic library and a static library, with the use of a makefile. In order to build two test applications that uses this libraries run on a terminal:

```bash
mkdir build
cd build
../configure --prefix=$(pwd)
make
make install
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/lib
```

## Author

* **Malcolm Davis** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
