close all;clear all;clc;

t = 0:0.01:10*pi;
x = t-sin(t);
y = 1-cos(t);
plot(x,y);