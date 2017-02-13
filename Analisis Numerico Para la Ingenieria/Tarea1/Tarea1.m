function [valorEsti, errorRel, errorAprox, terminos] = Tarea1(cifras, x)
    valorEsti = 0;
    terminos=0;
    if( nargin != 2)
      usage ( "Problema1(cifras, x)");
    endif
    cifras = 0.5*10**(2-cifras);
    errorAprox=100;
    while (cifras < errorAprox)
      valorEstiViejo = valorEsti;
      valorEsti += x**terminos/(factorial(terminos));
      errorAprox=(1-valorEstiViejo/valorEsti)*100;
      terminos++;
    endwhile
    errorRel =  (1 - valorEsti/exp(x)) *100;
endfunction