# Workshop 8

Eight assignment of the course CE-5303 "Introducción a los Sistemas Embebidos", second  semester 2018. Aims to exemplify Linux Drivers development.

## Prerequisites

The assignment can be downloaded and compiled for GNU/Linux distros, but I will focus on getting things up and running on a Linux Mint VM.  
***GCC compiler***  
It can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt update
sudo apt install gcc
```

***Linux-headers-version-generic***
They can be installed via the package manager.  
For example for debian based distros you can use apt:

```bash
sudo apt-get install linux-headers-$(uname -r)
```

## Theory Question

***Explain what are the two existing drivers handling and design spaces. Explain how each space handle the driver functions***
There are two types of driver spaces, the kernel one and the user one. For the first one, the hardware is handled directly via memory reads and writes. For the user space, the hardware is handled via the files provided by the operative system. There are 2 main functions that all drivers have, one for initalization and one for termination of the driver. The kernel space use module_exit and module_init in order to do this, on user space the equivalent is insmod and rmmod. The other common functions are open, close, read and write. In user space a fopen, fclose, fread, fwrite can be used, similary on kernel space this functions are memory interventions.

## Running

For this workshop the goal is to cross compile a new dynamic library for the raspberry gpio, you need to build the cross compiler tools and then you can run the make on a terminal and then load the module:

```bash
make -C /usr/src/linux-headers-$(uname -r) M=$(pwd modules)
sudo insmod nothing.ko
sudo rmmod nothing.ko
```

In the meantime you can use the driver.

## Author

* **Malcolm Davis** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)
