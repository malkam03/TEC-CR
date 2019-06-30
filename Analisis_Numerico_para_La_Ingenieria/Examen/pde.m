## Instituto Tecnológico de Costa Rica
## Área Académica de Ingeniería en Computadores
## CE-3102 Análisis Numérico para Ingeniería
## Prof. Pablo Alvarado
## II Semestre 2017
## Examen Final

## PROBLEMA 1

## NOMBRE:
## CARNE:

1;

###############
## Problema 1.1
## ¿Qué método va a usar y por qué?




###############
## Problema 1.2
## Perfiles térmicos

## Perfil término a lado izquierdo
function val=f_i(t)
  val = 0; # Corrija esto
endfunction

## Perfil térmico al lado derecho
function val=f_d(t)
  val = 0; # Corrija esto
endfunction

###############
## Problema 1.3
## Plantee el sistema de ecuaciones a resolver
## (puede hacerlo en un archivo aparte, si lo prefiere)



###############
## Problema 1.4
## Método de solución eficiente y apropiado para sistema de ecuaciones anterior


###############
## Problema 1.5
## Solucionador de sistema de ecuaciones anterior



###############
## Problema 1.6
## Solucionador de ecuación diferencial

## Solucionador de EDP para primer problema del examen
## Parámetros de salida:
##  T: matriz resultante con cada instante de tiempo en una fila
##  x: coordenadas en mm de cada columna de T
##  t: instante de tiempo de cada fila de T
## Parámetros de entrada:
##  longitud: tamaño en mm de la barra
##  dx      : distancia entre dos elementos discretos de la barra
##  total_t : total de segundos a resolver/simular
##  dt      : duración de paso temporal
##  fl      : función con perfil de temperatura a la izquierda
##  fd      : función con perfil de temperatura a la derecha
function [T,x,t]=solve_pde(longitud,dx,total_t,dt,fi=@f_i,fd=@f_d)
  x=0:dx:longitud;
  t=(0:dt:total_t)';

  nx=columns(x);
  nt=rows(t);

  if (nx<4)
    error("Elementos espaciales insuficientes");
  endif;

  if (nt<3)
    error("Elementos temporales insuficientes");
  endif;
  
  ## PONGA SU CÓDIGO AQUÍ:
  
endfunction



###############
## Problema 1.7
## Grafique la solución



###############
## Problema 1.8
## Estimación del error (puede plantear su estimación en hojas aparte)

