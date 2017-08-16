%% Examen Final
%% CE-Análisis numérico para ingeniería
%% I Semestre 2017
%% Nombre: Malcolm Davis
%% Carné: 201271325

%% Código para problema 1

1;

pkg load image;
close all;

%% Lea una imagen en grises normalizados
Aorig=imread("lenna.png");
A=double(Aorig)/255;

%% Implementación ingenua de la transformación
%% ADVERTENCIA: Este código es altamente ineficiente
function O=naive(I,T)
  c=columns(I);
  r=rows(I);
  O=zeros(r,c);
  % Para cada pixel de la imagen de entrada
  for y=1:r
    for x=1:c
      p=[x;y;1];
      q=T*p; % Calcule a cuál pixel se debe mapear (x,y)
      if ( (q(1)>=1) && (q(1)<=c) && (q(2)>=1) && (q(2)<=r) )
        % Cópielo en la imagen de salida, solo si es válido
        O(round(q(2)),round(q(1)))=I(y,x);
      endif        
    endfor;
  endfor;
endfunction;

%% Su solución al problema debe ir aquí
function O=smart(I,T)
  c=columns(I);
  r=rows(I);
  O=zeros(r,c);
  % Para cada pixel de la imagen de salida
  for y=1:r
    for x=1:c
      p=[x;y;1];
      q=p'*T'; % Calcule a cuál pixel se debe mapear (x,y) %se usa mapeo inverso
      if ( (q(1)>=1) && (q(1)<=c) && (q(2)>=1) && (q(2)<=r) )
        % Cópielo en la imagen de salida, solo si es válido
        O(x, y)=I(round(q(1)),round(q(2)));
      endif        
    endfor;
  endfor;
endfunction;


%% Construyendo una transformación sobre el centro de la imagen

%% Primer desplazamiento hacia cero
T0 = [1 0 -columns(A)/2;
      0 1 -rows(A)/2;
      0 0 1];

%% Invertir desplazamiento 
T1 = inv(T0);

%% Transformación prototipo
TP = [ 0.9 -0.5 0;
       1    0.7 0;
       0    0   1];

%% Transformación completa
T=T1*TP*T0;

%% Ejemplo aproximado de cómo debe verse la transformación
tic;
N=naive(A,T);
toc;

%% Calculando la solución propuesta
S=smart(A,T);

figure(1);
imshow(A);

figure(2);
imshow(N);

figure(3);
imshow(S);
