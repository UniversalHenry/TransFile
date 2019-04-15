close all;clear;clc;
%%
f=[2,-1,2];
A=[1,1,1;-2,0,1;0,-2,1];
b=[6,2,0];
Aeq=[];
beq=[];
lb=[0,0,0];
ub=[];
x0=[];
[x,fval] = linprog(f,A,b,Aeq,beq,lb,ub,x0);
x
fval