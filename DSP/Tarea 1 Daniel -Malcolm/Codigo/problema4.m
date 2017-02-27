function problema4()

F = 0.05; % Frecuencia a encontrar el Alias.
t= [0:1/F]; % rango de tiempo donde se ve la grafica SIEMPRE VA SER UN PERIODO
Y1 = sin(2*pi*F.*t);              %funcion temporal
alias = 2*pi*F+2*pi
Y2=sin(alias.*t);              %funcion temporal
subplot (1, 2, 1) 
plot(t,Y1); %grafica discreta de la funcion 1
title('Funcion Sinusoidal Discreta con f=.0.05'); %titulo
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f t)');% nombre eje y
subplot (1, 2, 2)
plot(t,Y2,'r');%grafica discreta de la funcion 2
title('Funcion Sinusoidal Discreta f=1.0500'); %titulo
xlabel('Numero de muestras');% nombre eje x
ylabel('Y(n) = sen(2pi f t)');% nombre eje y
endfunction