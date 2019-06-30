#First program of the second homework
function  problema1(x=1, factor=3, hmin=0.000000000000001)
  f = inline("0.3*x*x*x*x-0.15*x*x");
  df = (1.2*x*x*x-.3*x);
  h=1;
  H=[];
  back=[];
  forward=[];
  center=[];
  #Loop to fill the vectors
  while(h>hmin)
    h=h/factor;
    back = [back; (f(x-h)-f(x))/h];
    forward = [forward; (f(x+h)-f(x))/h];
    center = [center; (f(x+h)-f(x-h))/(2*h)];
    H=[H; h];
  endwhile
  if(nargin>3)
      print_usage ( "problema1(x, factor, hmin)");
      return
  endif

  
  eback = abs(back-df)/df;
  eforward = abs(forward-df)/df;
  ecenter = abs(center-df)/df;
  figure
  hold
  title ("Error In function of distance");
  xlabel ("Distance");
  ylabel ("Relative Error");
  loglog(H, eback);
  loglog(H, eforward, 'g');
  loglog(H, ecenter,  'r');
  legend('backward','forward','center');
  
  endfunction
