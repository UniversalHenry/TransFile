close all;clear all;clc;

t = 0:0.01:2*pi;
r = 1-cos(t);
x = r.*cos(t);
y = r.*sin(t);
plot(x,y);