close all;clear;clc;

x0 = [0.1,0.02];
tspan = 0:0.001:100;
odefun = @(t,x)[0,1;-0.5,-1.5] * x;
[t,x] = ode45(odefun,tspan,x0);

plot(t,x(:,1),t,x(:,2));
legend('x','v');