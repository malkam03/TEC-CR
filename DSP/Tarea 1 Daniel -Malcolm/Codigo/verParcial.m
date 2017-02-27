
function [Y] = verParcial (N)

f = [0.01,0.02,0.05,0.1]; % se crea un vector con la frecuencia con los diferentes valores 
n = [0:N]; % rango de muestras a tomar, en este punto el usuario tiene la capacidad 
           % de elegir el punto maximo, N. 


Y1 = sin(2*pi*f(1).*n); %funcion  1 con la frecuencia 1 
stem(n,Y1); %grafica discreta de la funcion 1
hold on 
grid on

Y2 = sin(2*pi*f(2).*n);%funcion  2 con la frecuencia 2

stem(n,Y2,'r');%grafica discreta de la funcion 2

Y3 = sin(2*pi*f(3).*n);%funcion  3 con la frecuencia 3

stem(n,Y3,'g');%grafica discreta de la funcion 3

Y4 = sin(2*pi*f(4).*n);%funcion  4 con la frecuencia 4

stem(n,Y4,'k');%grafica discreta de la funcion 4

title('Funcion Sinusoidal Discreta'); %titulo
axis([-2 (N+2), -1.2 1.2]) %dimensiones de los ejes
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f n)');% nombre eje y
legend('f = 0.01','f = 0.02','f = 0.05','f = 0.1'); %leyenda


hold off
endfunction
