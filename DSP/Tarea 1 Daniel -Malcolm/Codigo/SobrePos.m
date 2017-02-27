

function [Y] = SobrePos (F,tp,k)

TP= (1/F); % periodo de la sennal temporal
N = fix(TP/(tp)); %numero de muestras a partir del periodo de muestreo 
t= [0:0.000001:TP]; % rango de tiempo donde se ve la grafica SIEMPRE VA SER UN PERIODO
n = [0:N];% rango del numero de muestas

Y1 = sin(2*pi*F.*t);              %funcion temporal
Y2 = sin(2*pi*(F*tp).*n);         %funcion discreta
Y3 = sin(2*pi*(F*tp).*n +2*pi*k); %funcion alias

plot(t,Y1,'r'); %se grafica la funcion temporal 
hold on % se mantiene la misma ventana para el grafico
grid on % se activa el "grid"
stem(n*tp,Y2,'dg'); % graficacion de la funcion discreta 
stem(n*tp,Y3,'+-.m');% graficacion del alias de la funcion discreta 

title('Funcion Sinusoidal Temporal, Discreta y su Alias'); %titulo
xlabel('Tiempo (s)'); % nombre eje x
ylabel('Funcion sinusoidal');%nombre eje y 
legend('funcion temporal','funcion discreta','funcion alias');% leyenda de la grafica

hold off %se apaga la opcion de la ventana del grafico 


endfunction
