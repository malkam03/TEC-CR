# Workshop 7

Seventh assignment of the course CE-5303 "Introducción a los Sistemas Embebidos", second  semester 2018. Aims to exemplify the cross compilation and gpio use of a raspberry pi board.

## Prerequisites

The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.  
***GCC compiler***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt update
sudo apt install gcc
```

***Yocto***
The instructions to download and install it can be found at the oficial project page.

## Running

For this workshop the goal is to cross compile a new dynamic library for the raspberry gpio, you need to build the cross compiler tools and then you can run the make on a terminal:

```bash
make
```

## Author

* **Malcolm Davis** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
