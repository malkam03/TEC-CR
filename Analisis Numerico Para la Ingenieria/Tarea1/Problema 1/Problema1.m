function [valorEsti, errorRel, errorAprox, terminos] = Tarea1(cifras, x)
    if( nargin != 2)
      print_usage ( "Problema1(cifras, x)");
    endif
    #if(cifras > or 
    valorEsti = 0.0;
    terminos=0;
    cifras = 0.5*10**(2-cifras);
    errorAprox=100;
    valorEstiViejo =0.0;
    terminos = double(terminos);
    valorEsti = double(valorEsti);
    valorEstiViejo = double(valorEstiViejo);
    errorAprox = double(errorAprox);
    x = double(x);
    while (cifras < errorAprox)
      valorEstiViejo = valorEsti;
      valorEsti += x**terminos/(double(factorial(terminos)));
      errorAprox=(1-valorEstiViejo/valorEsti)*100;
      terminos++;
    endwhile
    errorRel =  (1 - valorEsti/exp(x)) *100;
endfunction