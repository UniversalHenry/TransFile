close all;clear;clc;
%%
d = [
12547	0.0321
12030	0.0316
10554	0.0336
8020	0.0356
7708	0.0338
5395	0.0381
3867	0.0371];
logd = log(d);
h_f = logd(:,1);
V = logd(:,2);