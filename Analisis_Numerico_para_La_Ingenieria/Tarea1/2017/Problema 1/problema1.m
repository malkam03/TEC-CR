function [val, errRel, errAprox, N] = problema1(n, x)
  if(nargin!=2)
      print_usage ( "problema1(n, x)");
      return
  endif
  if(n >15 | n<1)
    printf("Error, el número de cifras debe de ser un entero entre 0 y 15.");
    return
  endif
  format long;
  val = 0.0;
  valViejo =0.0;
  N=0;
  n = 0.5*10**(2-n);
  errAprox=100.0;
  while (n < errAprox)
    valViejo = val;
    val += x**N/(double(factorial(N)));
    errAprox=(1-valViejo/val)*100;
    N++;
  endwhile
  errRel =  (1 - val/exp(x)) *100;
  printf("El resultado de la operación e^%d es %f.\nEl error relativo porcentual aprox es %d%% y el verdadero es %d%%.\nSe tuvo que usar %d terminos.\n", x,val, errRel, errAprox, N)
endfunction
