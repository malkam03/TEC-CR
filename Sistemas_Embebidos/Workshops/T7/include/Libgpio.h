#ifndef LIBGPIO_H 
#define _LIBGPIO_H 
#include <stdlib.h>

extern int counter;
enum State {HIGH = 1, LOW = 0};

void enableGPIO(int pin);
void disableGPIO(int pin);
void pinMode(int pin,char* mode);
void digitalWrite(int pin,int value);
int digitalRead(int pin);
void blink(int pin, int freq, int time); 

#endif 
