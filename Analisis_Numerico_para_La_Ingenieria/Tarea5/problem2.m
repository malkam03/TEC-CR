#!/usr/bin/octave 
1;
%% Then the problem two with rungekutta4 and ode45 abd ode23  
function problem2()
  clear all
  close all
  pkg load odepkg
  xi = 0;
  xf = 200;
  y0= 5;
  h = 1/5;
  f = inline ("100 - y");
  %rungekutta4
  tic(); %starts the timer
  [x, y] = rungekutta4(f, xi, xf, y0, h(columns(h)));
  elapsed_time = toc(); %stops the timer and stores it
  %% Prints and plots
  disp ("The time for 4th order rungekutta is:"), disp (elapsed_time)
  disp ("Using this quantity of points:"), disp (columns(x))
  plot(x,y,'color','r',";rungekutta4;"); hold on;
  %ode45
  tic();%starts the timer
  [x, y] = ode45 (f, [xi, xf], y0);
  elapsed_time = toc(); %stops the timer and stores it
  %% Prints and plots
  disp ("The time for ode45 is:"), disp (elapsed_time)
  disp ("Using this quantity of points:"), disp (rows(x))
  warning('off',  'Octave:possible-matlab-short-circuit-operator');
  plot(x,y,'color','b',";ode45;"); hold on;
  %ode23
  tic();%starts the timer
  [x, y] = ode45 (f, [xi, xf], y0);
  elapsed_time = toc(); %stops the timer and stores it
  %% Prints and plots
  disp ("The time for ode23 is:"), disp (elapsed_time)
  disp ("Using this quantity of points:"), disp (rows(x))
  warning('off',  'Octave:possible-matlab-short-circuit-operator');
  plot(x,y,'color','g',";ode23;"); hold on;
  title({"Problem 2","rungekutta, ode45 and ode23"});
  xlabel ("x");
  ylabel ("y");
  disp ("Press enter to continue")
  pause () 
endfunction
problem2