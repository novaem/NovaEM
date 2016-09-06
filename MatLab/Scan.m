clear all;
close all;
clc;

% Speed of light:

speedOfLight = 299792458;

% Center frequency:

fCenter = 77e9;

% Wave length at center frequency:

lambdaCenter = speedOfLight / fCenter;

% Physical distance between adjacent array elements:

d = lambdaCenter  * 0.45 ;

% Frequency to be investigated:

f = 70e9;

% Wave length at frequency to be investigated:

lambda = speedOfLight / f;

% Wave number at frequency to be investigated:

beta = 2*pi / lambda;

% Phase difference of excitations between adjacent array elements:

alpha = 60.0;

alpha = alpha / 180.0 * pi;

angle = acos(-alpha / (beta * d)) * 180 / pi;

% Angular shift of the main lobe:

shift = angle - 90;

display('The angular shift of the main lobe is:');

display(shift);

