clear all;
close all;
clc;

r0 = [-1, -1/sqrt(3), -1/sqrt(6)]';
r1 = [1, -1/sqrt(3), -1/sqrt(6)]';
r2 = [0, 2/sqrt(3), -1/sqrt(6)]';
r3 = [0, 0, 3/sqrt(6)]';

x = 0.5;
y = 0.2;
z = 0.1;

w = (z * sqrt(6) + 1) / 4;

v = y / sqrt(3) + (1 - w) / 3;

u = (x + 1 - w - v) / 2;



r = (1 - u- v - w) * r0 + u * r1 + v * r2 + w * r3;

x
y
z

r