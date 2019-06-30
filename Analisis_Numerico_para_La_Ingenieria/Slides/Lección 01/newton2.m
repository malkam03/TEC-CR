#!/usr/bin/octave

t=[0:0.01:30]; # Tiempo [s]
m=80;          # Masa [kg]
g=9.8;         # Aceleración gravitacional [m/s^2]
c=12.5;        # Coeficiente de arrastre [kg/s]

# Solución analítica con velocidad inicial cero
va=m*g/c*(ones(size(t))-exp(-c*t/m));
hold off;
plot(t,va,'k',"linewidth",2);
hold on;
plot(t,m*g/c*ones(size(t)),'r');

# Solución aproximada
#dt = 1;                # time step [s]
dt = .1;                # time step [s]
ts = 0:dt:t(length(t)); # time samples
vs = zeros(size(ts));
imax = length(ts);

for i=2:imax
  vs(i) = vs(i-1) + (g-c*vs(i-1)/m)*dt;
endfor

plot(ts,vs,'xr');
plot(ts,vs,'b');

xlabel("t");
ylabel("v");
		 
