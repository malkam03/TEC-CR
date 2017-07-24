%% Examen Final
%% CE-Análisis numérico para ingeniería
%% I Semestre 2017
%% Nombre: Malcolm Davis
%% Carné: 201271325

%% Código para problema 2

1;

pkg load image;

close all;

%% Muestre la imagen pero ajustando el contraste de forma logaritmica
function logimshow(A)

  valmax=1000;
  mn=min(A(:));
  mx=max(A(:));

  m=(valmax-1)/(mx-mn);
  b=1-m*mn;
  
  normaA=1./log(valmax);
  AA=log(m*A+b)*normaA;

  imshow(AA);
endfunction;

%% Lea una imagen en grises normalizados
Aorig=imread("lenna.png");
A=double(Aorig)/255;

%% Calcule la transformada de Fourier de A
FA = fft2(A);

%% Muestre la magnitud del espectro
figure(1);
logimshow(abs(FA));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 2.1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% PONGA SU SOLUCIÓN AQUÍ:

%% MODIFIQUE B PARA CENTRAR EL ESPECTRO
B =A;
% a los elementos que se encuentran en un m*n impar los multiplica por -1
B(2:2:end, 1:2:end)=B(2:2:end, 1:2:end)*-1;
B(1:2:end, 2:2:end)=B(1:2:end, 2:2:end)*-1; 

FB=fft2(B);
figure(2);
logimshow(abs(FB));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 2.2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Cout=double(imread("qlenna.png"))/255;
FC=fft2(Cout);
FC(2:2:end, 1:2:end)=FC(2:2:end, 1:2:end)*-1;
FC(1:2:end, 2:2:end)=FC(1:2:end, 2:2:end)*-1; 
%% MODIFIQUE EL ESPECTRO PARA CORREGIR DESPLAZAMIENTO
FD=FC;

%% Calcular la función y eliminar ruido numérico
C=real(ifft2(FD));

figure(3);
imshow(C);
