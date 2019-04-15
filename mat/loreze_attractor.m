close all;clear;clc;

dt = 0.002;
tspan = 0:dt:200;
y0 = [1,1,1]';
sigma = 16;
r = 45.92;
b = 4;
[t,y] = ode45(@(t,x)func(x,sigma,r,b),tspan,y0);

figure(1);
subplot(231);
plot(y(:,1),y(:,2));
grid on;
title('x ys y');
xlabel('x');
ylabel('y');
subplot(232);
plot(y(:,2),y(:,3));
grid on;
title('y ys z');
xlabel('y');
ylabel('z');
subplot(233);
plot(y(:,3),y(:,1));
grid on;
title('z ys x');
xlabel('z');
ylabel('x');
subplot(234);
plot(y(:,1),t);
grid on;
title('x ys t');
xlabel('t');
ylabel('x');
subplot(235);
plot(y(:,2),t);
grid on;
title('y ys t');
xlabel('t');
ylabel('y');
subplot(236);
plot(y(:,3),t);
grid on;
title('z ys t');
xlabel('t');
ylabel('z');

figure(2);
plot3(y(:,1),y(:,2),y(:,3));
grid on;
title('x vs y vs z');
xlabel('x');
ylabel('y');
zlabel('z');

function dx = func(x,sigma,r,b)
dx = zeros(size(x));
dx(1) = sigma*(x(2) - x(1));
dx(2) = -x(1).*x(3) + r*x(1) - x(2);
dx(3) = x(1).*x(2) - b * x(3);
end