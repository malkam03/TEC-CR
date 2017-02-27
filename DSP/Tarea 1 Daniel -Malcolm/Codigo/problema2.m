
function  problema2 ()

f = [0.01,0.02,0.05,0.1]; % se crea un vector con la frecuencia con los diferentes valores 
n = [0:49]; % sce define el rango desde 0 hasta 49 (las primeras 50 muestras)


Y1 = sin(2*pi*f(1).*n); %funcion  1 con la frecuencia 1
Y2 = sin(2*pi*f(2).*n);%funcion  2 con la frecuencia 2
Y3 = sin(2*pi*f(3).*n);%funcion  3 con la frecuencia 3
Y4 = sin(2*pi*f(4).*n);%funcion  4 con la frecuencia 4

subplot (2, 2, 1) 
stem(n,Y1); %grafica discreta de la funcion 1
title('Funcion Sinusoidal Discreta con f=.0.01'); %titulo
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f n)');% nombre eje y
subplot (2, 2, 2)
stem(n,Y2,'r');%grafica discreta de la funcion 2
title('Funcion Sinusoidal Discreta f=.0.02'); %titulo
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f n)');% nombre eje y
subplot (2, 2, 3)
stem(n,Y3,'g');%grafica discreta de la funcion 3
title('Funcion Sinusoidal Discreta f=.0.05'); %titulo
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f n)');% nombre eje y
subplot (2, 2, 4)
stem(n,Y4,'k');%grafica discreta de la funcion 4
title('Funcion Sinusoidal Discreta f=.0.1'); %titulo
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f n)');% nombre eje y


endfunction
