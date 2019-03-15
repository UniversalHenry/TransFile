close all;clear all;clc;

t = 0:0.01:2*pi;
a = 1;
x = a*sin(3*t).*cos(t);
y = a*cos(3*t).*sin(t);
plot(x,y);