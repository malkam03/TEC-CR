function [v,ev,ea,n]=anpi_erf(x,c)
  if(nargin!=2)
      print_usage ( "anpi_erf(x,c)");
      return
  endif
  if(c >15 | c<1)
    printf("Error, el número de cifras debe de ser un entero entre 0 y 15(usando long).");
    return
  endif
  format long;
  v=0.0;
  c=0.5*10**(2-c);
  n=0;
  ea=100.0;
  constant=2/(sqrt(pi));
  while (c < ea)
    vold = v;
    v += constant*((-1)**n)*x**(2*n+1)/(factorial(n)*(2*n+1));
    ea=abs(1-vold/v)*100;
    n++;
  endwhile
  ev=abs(1-v/erf(x))*100;
  printf("El resultado de la operación anpi_erf(%d) es %9.15f.\nEl resultado de la operación erf(%d) es %9.15f.\nEl error relativo porcentual aprox es %d%% y el verdadero es %d%%.\nSe tuvo que usar %d terminos.\n", x,v, x, erf(x),ea, ev, n)
endfunction