%% Rungen Kutta 4th order method
% f is the matematical function to evaluate f = inline ("x*y^2")
% xi is the start of the x interval
% xf is the last x of the interval
% y0 is the value of the y0 to evaluate f(x0, y0)
% h is the step size
function  [ x , y ]= rungekutta4( f , xi , xf , y0 , h)
  %  Aplique el ḿetodo RK4 para resolver dy/dx=f(x,y)
  %  con   y(xi)=y0, entre xi y xf
  %  La salida x=xi: h: xf
  %  La salida y seŕa  la solucíon a la EDO
  if (nargin != 5)
    error ("usage: rungekutta4( f , xi , xf , y0 , h)");
  endif
  if(!isscalar(xi) )
    error ("xi must be a scalar");
  endif
  if(!isscalar(xf) )
    error ("xf must be a scalar");
  endif
  if(!isscalar(y0) )
    error ("y0 must be a scalar");
  endif
  if(!isscalar(h) )
    error ("h must be a scalar");
  endif
  formula(f);
  y = y0;
  x = xi:h:xf;
  for i = 1:(columns(x)-1) %For each i from 1 to the length of the x vector
    % Using the popular constants and the method seen in class
    k1 = f(x(i), y(i));
    k2 = f(x(i)+0.5*h, y(i)+0.5*h*k1); 
    k3 = f(x(i)+0.5*h, y(i)+0.5*h*k2); 
    k4 = f(x(i)+h, y(i)+h*k3);
    y = [y, y(i)+h/6*(k1+2*k2+2*k3+k4)];  
  endfor
endfunction