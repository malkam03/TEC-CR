## Instituto Tecnológico de Costa Rica
## Área Académica de Ingeniería en Computadores
## CE-3102 Análisis Numérico para Ingeniería
## Prof. Pablo Alvarado
## II Semestre 2017
## Examen Final

## PROBLEMA 2

## NOMBRE: Malcolm Davis
## CARNE: 201271325

2;

## Cargar los datos
X=load("-ascii","regresion.dat");
# Funcion a evaluar
func = inline("a*x.^2+ b*x .+c");
###############
## Problema 2.1
## Grafique los puntos bidimensionales

figure(1);
clf;
%Con X(row, [columns]) obtiene las xs y ys.
scatter(X(1, [1:columns(X)]), X(2, [1:columns(X)]), 'b', "x");
xlabel("X Coordinate");
ylabel("Y Coordinate");
title ({"Scatter Plot"; ...
         "Data for Regresion"});
hold

disp ("Press enter to continue")
pause () 
###############
## Problema 2.2
## Implemente la función de error

function val=f(abc,X)
  ## abc: vector columna [a,b,c]' con los parámetros de la función cuadrática
  ## X:   datos para evaluar la función, un dato por columna
  % Como los elementos son vectores, se aprovecha esto para no tener que hacer un ciclo. 
  % Se hacen las operaciones vectoriales (escalar el vector de xs^2 con a y así sucesivamente.
  % Por último suma los elementos del vector de errores resultantes en val.
  val = sum((X(2, :) - (abc(1)*(X(1, :).^2)+abc(2)*X(1, :) + ones(1,columns(X)) *abc(3))).^2);
  
endfunction

###############
## Problema 2.3
## Implemente el gradiente de la función de error
function val=gf(abc,X)
  ## abc: vector columna [a,b,c]' con los parámetros de la función cuadrática
  ## X:   datos para evaluar la función, un dato por columna
  %Utilizando el mismo principio del punto anterior, y el methodo visto en clase 
  %para minimos cuadrados(presentación 15, diapositiva 18), se calcula primero una 
  %parte que se repite de la derivada y luego se agregan las diferencias y se suman los vectores
  tmpgf = -2*(X(2, :) - (abc(1)*(X(1, :).^2)+abc(2)*X(1, :) .+ abc(3)));
  gfa = sum((X(1, :).^2).*tmpgf); 
  gfb = sum((X(1, :)).*tmpgf); 
  gfc = sum(tmpgf);
  val=[gfa, gfb, gfc]'; 
endfunction
###############
## Problema 2.4

function [ABC,err]=optimice(f,gf,X,lambda,tol,abc0=[0,0,0]')
  ## f      es el handler de la función a optimizar
  ## gf     es el handler que calcula el gradiente de f
  ## X      es la matriz de datos 
  ## lambda es el tamaño de paso del descenso de gradiente
  ## tol    es el umbral de tolerancia para determinar convergencia
  ## abc0   es un vector [a0,b0,c0] especificando el punto inicial de
  ##        la optimización
  ## ABC    es una matrix de n x 3, donde cada fila corresponde a un
  ##        paso en el proceso de optimización.  Es decir, ABC(:,1)
  ##        corresponde siempre a abc0, y ABC(:,rows(ABC)) corresponde
  ##        a los parámetros óptimos.
  ## err    es el vector conteniendo los errores en cada paso

  if ( (rows(abc0)!=3) || columns(abc0)!=1 )
    error("Vector inicial no tiene forma 3x1");
  endif;
  maxIterations = 200;

  ABC = abc0;
  err = 2*tol;
  # Se utiliza la regla del delta para definir el siguiente valor optimo
  do 
    # Se agrega el nuevo elemento al vector ABC
    ABC = [ABC, ABC(:, columns(ABC)).-lambda*gf(ABC(:, columns(ABC)), X)];
    # Se agrega el nuevo elemento al vector de error
    err = [err, f(ABC(:, columns(ABC)), X)];
    if (columns(ABC) > maxIterations);
      break
    endif
  until( err(columns(err)) < tol)
  # Elimina el primer error porque era uno para inicializar la variable
  err = err(2:columns(err));


  
endfunction

## Llame al optimizador con la interfaz anterior

lambda=.5e-3;  # Se cambió a este valor por el dominio
tol=1e-7; # Se ajustó este valor para aproximarlo a un valor torelable
[ABC,err]=optimice(@f,@gf,X,lambda,tol,[1,1,1]'); # Se ejecuta el optimize

###############
## Problema 2.5
## Imprima el conjunto óptimo de parámetros
#Para evitar un bug en el ploteo se acomodan los xs
[sorted_xs, idk] = sort(X(1,:));
# Se selecciona el último valor de ABC osea el optimo
optimo = ABC(:, columns(ABC))
# Grafica el optimo
plot(sorted_xs, func(optimo(1), optimo(2), optimo(3), sorted_xs), 'color','r',";Optimal Value;"); 
disp ("Press enter to continue")
pause () 

###############
## Problema 2.6
## Muestre el error en función de las iteraciones
figure(2);
xlabel("Iteration");
ylabel("Error");
# Se plotea el error
plot(err);
disp ("Press enter to continue")
pause () 

###############
## Problema 2.7
## Muestre las curvas inicial, intermedias y final ajustadas a los datos
figure(1);
# Por último se plotean el primero los intermedios en un ciclo y el final
# con diferentes colores
plot(sorted_xs, func(ABC(1, 1), ABC(2,1), ABC(3,1), sorted_xs), 'color','black','LineWidth', 3,';First;');
plot(sorted_xs, func(ABC(1, 2), ABC(2,2), ABC(3,2), sorted_xs), 'color', 'c',';Intermediate;'); 
for (i = 3:(columns(ABC)-1))
  plot(sorted_xs, func(ABC(1, i), ABC(2,i), ABC(3,i), sorted_xs), 'color', 'c');         
endfor
plot(sorted_xs, func(ABC(1, columns(ABC)), ABC(2,columns(ABC)), ABC(3,columns(ABC)), sorted_xs), 'color','red', 'LineWidth', 3,';Optimal;');
hold on;
disp ("Press enter to continue")
pause () 

