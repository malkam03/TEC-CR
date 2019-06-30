function  diferencias_divididas(x=1, factor=.95)
  if(nargin>2)
      print_usage ( "problema1(x, factor, hmin)");
      return
  endif
  hmin = 0.1*10**(-14);
  f = inline("sin(e^(x^2))");
  df = (cos(e**(x**2))*e**(x**2)*2*x);
  h=1;
  H=[];
  back=[];
  forward=[];
  center=[];
  #Loop to fill the vectors
  while(h>hmin)
    h=h*factor;
    back = [back; (f(x)-f(x-h))/h];
    forward = [forward; (f(x+h)-f(x))/h];
    center = [center; (f(x+h)-f(x-h))/(2*h)];
    H=[H; h];
  endwhile  
  eback = abs(df-back)/df;
  eforward = abs(df-forward)/df;
  ecenter = abs(df-center)/df;
  figure
  hold
  title ("Error In function of distance");
  xlabel ("Distance");
  ylabel ("Relative Error");
  loglog(H, eback);
  loglog(H, eforward, 'g');
  loglog(H, ecenter,  'r');
  set (gca, "ydir", "reverse");
  legend('backward','forward','center', "location", "north");
  
  endfunction
