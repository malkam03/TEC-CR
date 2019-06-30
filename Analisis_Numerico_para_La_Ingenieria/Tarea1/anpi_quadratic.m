function [x1,x2,X1,X2]=anpi_quadratic(a, b, c, precision)
  if(nargin!=4)
      print_usage ( "anpi_quadratic(a, b, c, @precision)");
      return
  endif
  if(precision != @single && precision != @double)
    printf("Error, la presicion debe de ser single o double.");
    return
  endif
  a=precision(a);
  b=precision(b);
  c=precision(c);
  # Formula tipica
  x1 = (-b+sqrt(b*b-4*a*c))/(2*a); 
  x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
  # Formula alternativa
  X1 = -(2*c)/(b+sqrt(b*b-4*a*c));
  X2 = -(2*c)/(b-sqrt(b*b-4*a*c));
  printf("Las raices de la ecuación %fx^2+%fx+%f son con la formula tradicional:\nx1:%f y x2:%f\nY con la formula alternativa\nx1:%f y x2:%f\n", a,b,c,x1,x2,X1,X2)
endfunction