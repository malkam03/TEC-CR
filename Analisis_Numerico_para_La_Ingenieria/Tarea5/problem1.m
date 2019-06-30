#!/usr/bin/octave 
1;
%%First Rungen Kutta 4th order
function problem1()
  clear all
  close all
  xi = 0;
  xf = 1;
  y0= 1;
  h = 1/8;
  f = inline ("x*y^2");
  e = [];
  while (h(columns(h)) >= 1/1024)
    [x, y] = rungekutta4(f, xi, xf, y0, h(columns(h)));
    e = [e, abs(2-y(columns(y)))/2];
    h=[h,h(columns(h))/2];
  endwhile
  figure (1);
  plot(x, y);
  title ("4th Order Rungekutta Results");
  xlabel ("x");
  ylabel ("y");
  figure (2);
  semilogy(h(1:columns(h)-1), e);
  title ({"semilogy() plot of the error", "y-axis is logarithmic"});
  xlabel ("h");
  ylabel ("error");
  disp ("Press enter to continue")
  pause () 
endfunction
problem1