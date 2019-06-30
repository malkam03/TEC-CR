# Tarea 1
First assignment of the course CE-3102 "Análisis Numérico para Ingeniería", second semester 2018. Aims to test some errors related to calculations with simple and double precision.

## Prerequisites
The assignment can be download and compiled for both Windows and GNU/Linux distros, but I'll focus on getting things up and running for the latter.   
***Octave***
It can be installed via the package manager.   
For example for debian based distros you can use apt:
```
sudo apt update
sudo apt install octave
```
## Running/Results

- For the ***first*** problem, just cd to this folder from octave command line and then cal the function with:
```
[v,ev,ea,n]=anpi_erf(x,c)
```
This will store the values of the result on [v,ev,ea,n] variables. And also this function will print in a formated mode the results of the function.   
- The ***second*** problem requires us to calculate the binary representation of the number 0.1:   
Using the provided hint:
```
0.1(dec)=1(dec)/10(dec)=0001(bin)/1010(bin)
```
And performing a long division:
```
0001(bin)/1010(bin)=0.0001100110011...(bin)
```
- The ***third*** problem is to inspect the output of this commands:
```
>> output_precision(30)
>> a=single(.1)
a =    1.00000001490116119384765625000e-01
>> b=double(.1)
b =    1.00000000000000005551115123126e-01
>> double(a)-b
ans =    1.49011611383365050187421729788e-09
```
The first one is to set the terminal to output 30 digits.   
The second one is the equivalent to a cast to single, it will force a to be the single precision representation of 0.1.  
The third one will do the same as the second one but with double precision representation and with variable b.    
The last one will "cast" from single to double and then subtract them. But since they were represented at the beginning with different precisions and as it can be observed on the output, the subtraction of both wont be zero.   
- The ***last*** problem is another octave one, in order to run it just go to octave command line and type:
```
anpi_quadratic(a,b,c,precision)
```
For this problem, an example had to be ran and the output had to be analyzed:
```
>> anpi_quadratic(1,6000.0002,1.2,@single);
Las raices de la ecuación 1.000000x^2+6000.000000x+1.200000 son con la formula tradicional:
x1:-0.000244 y x2:-6000.000000
Y con la formula alternativa
x1:-0.000200 y x2:-4915.200195
>> anpi_quadratic(1,6000.0002,1.2,@double);
Las raices de la ecuación 1.000000x^2+6000.000200x+1.200000 son con la formula tradicional:
x1:-0.000200 y x2:-6000.000000
Y con la formula alternativa
x1:-0.000200 y x2:-6000.000002
```
As it can be observed, for both formulas and when using double precision the errors obtained by representation are hardly noticeable. But when using just single precision, the representation and the division of a larger or smaller number comes into play increasing the error.

## Author
* **Malcolm Davis** - *Initial work* - [ITCR/Análisis Númerico para la Ingienería/Tarea 1](https://github.com/malkam03/ITCR/tree/Analisis_Numerico_para_la_Ingenieria/Tarea1)

## License

This project is licensed under the MIT License - see the [LICENSE.md](../../../LICENSE.md)


