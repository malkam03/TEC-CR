# Workshop 3
Third assignment of the course CE-4302 "Arquitectura de Computadores II", first semester 2018. Aims to exemplify the use of OpenMP+NEON on a android device.

## Prerequisites
The assignment can be downloaded and compiled for both Windows and GNU/Linux distros, but I will focus on getting things up and running for the latter.     
***GCC compiler***    
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install gcc
```
***MPICH***
It can be installed via the package manager.
Just type:
```
sudo apt install mpich
```
***Android Tools***    
Download the ndk from https://developer.android.com/ndk/downloads/. And install adb and fastboot with:
```
sudo apt install android-tools-fastboot android-tools-adb
```
## Running

To compile the programs just use the compile script on a terminal to build them all:
```
./compile.sh
```

To run them all use the script typing on a terminal:
```
./execute.sh 
```
Or send the bin file and run on the android device with:
```
adb push <target>/libs/armeabi-v7a/<target> /data/local/tmp
adb shell /data/local/tmp/<target> 
```
## Author
* **Malcolm Davis** - *Initial work*
* **Jefferson Gonzalez** - *pi_neon files*

## License
This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md).
