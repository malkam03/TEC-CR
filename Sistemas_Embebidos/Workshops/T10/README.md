# Workshop 10

Tenth assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the simulation of hardware modules.

## Prerequisites

The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter(pthreads in windows are possible but a little tricky).  
***Python3***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt update
sudo apt install python3
```

## Running

For this workshop the goal is to simulate hardware for both fibonacci and factorial succesions. A python script for each can be run with:

```bash
./fibonacci.py [max]
./factorial.py [max]
```

The max argument can be added or not and he script will use default values.  

## Author

* **Malcolm Davis** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
