# Workshop 4
Fourth assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use of CUDA on a Jetson TX2.

## Prerequisites
The assignment can be downloaded and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.      

***Jetson TX2***    
For this project we use the Jetson TX2 platform, but any other CUDA compatible card can be used.

***CUDA Toolkit***
Installation instructions for this can be found on https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html.

## Running

To build the programs just use go to the respective folder and type:
```
make
```

To run them with the default values just typing on a terminal:
```
./target
```

The targets can be:
* **vecadd:** Vector addition with cuda example
* **matrixMult:** Matrix multiplication with cuda
* **saxpy:** SAXPY function with cuda

## Author
* **Malcolm Davis** - *Initial work*

## Acknowledgements
* **lzhengchun** - The CUDA matrix code was based on his [own](https://github.com/lzhengchun/matrix-cuda)

## License
This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md).
The helloCUDA example is not mine and it got another [LICENSE.md](helloCUDA/LICENSE).
