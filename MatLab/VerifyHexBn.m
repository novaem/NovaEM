clear all;
close all;
clc;

lc = [1/3, 1/3, 1/3]';

p0 = [0.0, 0.0, 0.0]';
p1 = [0.5, 0.0, 0.1]';
p2 = [0.6, 0.7, 0.2]';
p3 = [0.2, 0.8, 0.3]';
p4 = [-0.2, 0.1, 1.0]';
p5 = [1.0, 0.2, 0.9]';
p6 = [0.8, 0.8, 0.8]';
p7 = [0.2, 1.0, 0.7]';

u = lc(1);
v = lc(2);
w = lc(3);

x = 1.0 - u;
y = 1.0 - v;
z = 1.0 - w;

uHat = y * z * (p1 - p0) + v * z * (p2 - p3) + ...
       y * w * (p5 - p4) + v * w * (p6 - p7);

vHat = z * x * (p3 - p0) + z * u * (p2 - p1) + ...
       w * x * (p7 - p4) + w * u * (p6 - p5);
       
wHat = x * y * (p4 - p0) + u * y * (p5 - p1) + ...
       u * v * (p6 - p2) + x * v * (p7 - p3);

uHat * u

vHat * v

-uHat * x

-vHat * y

wHat * w

-wHat * z

