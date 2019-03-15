close all;clear all;clc;

t = 0:0.01:10*pi;
x = cos(t)+t.*sin(t);
y = sin(t)-t.*cos(t);
plot(x,y);
