%% Examen Final
%% CE-Análisis numérico para ingeniería
%% I Semestre 2017
%% Nombre:
%% Carné:

%% Código para problema 4

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

%% Muestre la imagen pero ajustando el contraste de forma lineal
function linimshow(A)

  mn=min(A(:));
  mx=max(A(:));

  m=1/(mx-mn);
  b=-m*mn;
  
  AA=m*double(A)+b;

  imshow(AA);
endfunction;


%% Lea la imagen a evaluar
Aorig=imread("low_contrast.jpg");
figure(1);
hold off;
imshow(Aorig);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 4.1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% PONGA SU SOLUCIÓN AQUÍ
contraste = 1.5;
mn = double(min(Aorig(:)));
mx = double(max(Aorig(:)));
C=(double(Aorig)-mn)/(mx-mn)*contraste; %% << Corrija el contraste
figure(2);
imshow(C);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 4.2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

S=im2bw(C); %% << Mejorar esto con un método de selección de umbral
figure(3);
imshow(S);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 4.3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

N= bwmorph (S, 'close', inf); 
N= bwmorph (N, 'diag', inf); 
N= bwmorph (N, 'majority', inf); 
figure(4);
imshow(N);
