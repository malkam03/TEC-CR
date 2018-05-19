# Project 2 Beowulf Cluster Image Filter
Second project of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify parallel procesing on diferent computers. The image will be distributed on diferent nodes of the cluster and then filtered(it is better to do parallel read and write on the image but it'll be implemented the other way to apprecitate the comunication overhead).

## Prerequisites
The assignment can be download and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.      
This code is intended to run over a beowulf cluster, but it can be compiled and run on a regular computer. You can use some [Beowulf setup tutorial](http://mpitutorial.com/tutorials/running-an-mpi-cluster-within-a-lan/) if you need help setting it up.  

***GCC compiler***    
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install gcc
```

***OpenCV***    
Opencv is used for image operations, so you should install it to compile the project. You can find the installation instructions on the official [webpage](https://www.learnopencv.com/install-opencv3-on-ubuntu/).

***MPICH***
It can be installed via the package manager with the following command:
```
sudo apt install mpich mpichlib-dev
```

## Running

To compile the program just type make on a terminal:
```
make
```
Two targets will be compiled, imageFilter_MPI for just MPI parallelization and imageFilter_MPI_OMP or both MPI and OMP parallelization.     
To run it type on a terminal:
```
./<target> filePath variance*
```
Arguments with a '*' are optional, defaults will be used in case the user don't provide one. 
* **filePath** to load a file with the file path as the value,
* **variance** The variance for the filter,      
## Authors
* **Malcolm Davis** - *Initial work* 
* **Luis Barboza** - *Initial work*
* **Sebastian Viquez** - *Initial Work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
