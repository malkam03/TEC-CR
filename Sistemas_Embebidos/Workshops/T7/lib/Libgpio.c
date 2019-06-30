/** @file Libgpio.c
 * 
 * @brief Source file with the 2nd workshop solution 
 * @author Malcolm Davis
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * Exports the pin into the system file
 */
void enableGPIO(int pin){
    char run[60];
    sprintf(run, "echo %d > /sys/class/gpio/export", pin);
    system(run);    
}

/**
 * Unexport the pin into the system file
 */
void disableGPIO(int pin){
    char run[60];
    sprintf(run, "echo %d > /sys/class/gpio/unexport", pin);
    system(run);    
}

/**
 * Set the pin mode into the system file
 */
void pinMode(int pin, char * mode){
    char run[60];
    sprintf(run, "echo %s > /sys/class/gpio/gpio%d/direction", mode,pin);
    system(run);    
}

/**
 * Write data on a pin
 */
void digitalWrite(int pin, int * value){
    char run[60];
    sprintf(run, "echo %d > /sys/class/gpio/gpio%d/value", value,pin);
    system(run);    
}

/**
 * Read data on a pin
 */
int digitalRead(int pin){
    char valueLine[10];
    char run[60];
    sprintf(run, "cat /sys/class/gpio/gpio%d/value", pin);
    FILE* file = popen (run, "r");
    fgets(valueLine, sizeof(valueLine), file);
    return atoi(valueLine);
}

/**
 * BLink a led with some frequency for some time
 */
void digitalWrite(int pin, int freq, int time){
    char turnOn[60];
    char turnOff[60];
    sprintf(turnOn, "echo 1 > /sys/class/gpio/gpio%d/value", pin);
    sprintf(turnOff, "echo 0 > /sys/class/gpio/gpio%d/value", pin);
    for(int start=0; start<time;start+=2*freq){
        system(turnOn);
        sleep(freq);
        system(turnOff);
        sleep(freq);
    }
}