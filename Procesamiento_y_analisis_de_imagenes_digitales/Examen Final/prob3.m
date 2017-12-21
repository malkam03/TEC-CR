%% Examen Final
%% CE-Análisis numérico para ingeniería
%% I Semestre 2017
%% Nombre: Malcolm Davis
%% Carné: 201271325

%% Código para problema 3

1;

pkg load image;
pkg load geometry; % <-- Para poder usar drawCircle

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
Aorig=imread("naranjas.jpg");
figure(1);
hold off;
imshow(Aorig);

%% Extraiga los canales R,G,B
R=Aorig(:,:,1);
G=Aorig(:,:,2);
B=Aorig(:,:,3);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 3.1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% PONGA SU SOLUCIÓN AQUÍ:

C=double(R*0.4-G*0.16-B*0.4)/255;
figure(2);
imshow(C);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 3.2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Extraiga los bordes de la imagen de grises utilizando Canny, pero
%% ajuste los umbrales para que la detección de los bordes queden
%% claros

thr=[min(C(:)) max(C(:))];
%%E=edge (C, "Canny"); %% <---- with the default values
%%figure(4);
%%imshow(E); 

%E=edge (C, "Canny", thr);%% <---- with the params
%figure(5);
%imshow(E);

E=edge (C, "Canny", thr, 2.0522);%% <---- with the default values
figure(6);
imshow(E);




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Problema 3.3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Programe aquí su propuesta de detección de los círculos.
%% Modularice con funciones tareas complejas.
%Methodo para elegir los circulos
function Circles=choose(R,C,Sizes)
  Circles = [C(1) R(1) Sizes(1)];
  % Para cada pixel de la imagen de entrada
  for y=2:columns(C)
  	add = true;
  	actualsize = Sizes(1+idivide ((columns(Sizes)-1)*y, columns(C), "floor"));
    for x=y+1:columns(C)
	  	if (C(y) < C(x)+actualsize && C(y)> C(x)-actualsize  && R(y) < R(x)+actualsize && R(y) > R(x)-actualsize  )
	  		add=false;
	    endif
    endfor
    if (add)
    	Circles = [Circles; C(y) R(y) actualsize]; 
    endif
  endfor
endfunction

minSize = 23;
maxSize = 33;
maxObjects =30;
R=[];
C=[];
Sizes= [minSize:maxSize];
H = hough_circle(E, Sizes);
for i=1:columns(Sizes)
	[r, c, hnew] = houghpeaks(H(:,:,i), maxObjects);
	R = [R r];
	C = [C c];
endfor
figure(7);
imshow(Aorig);
hold ("on");
Circles = choose(R(:, 2:columns(R)),C(:, 2:columns(C)),Sizes);
h = drawCircle(Circles);
imshow (h);
hold ("off");

