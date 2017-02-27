function tono = Tono(N)

f= 440; %frecuia de oscilacion 
fs= 1/N; %frecuecia de muestreo
t= [0:N:1]; %tiempo de duracion
s= sin(2*pi*f*t); %funcion seno

wavwrite(s,fs,'sonido_la440.wav');%crea el archivo a reproducir
soundsc(s,fs); %hace reproducir el sonido creado por el seno

endfunction
