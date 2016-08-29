clear all;
close all;
clc;

% Freespace wavelength:

lambda = 1;

% Freespace wave number:

beta = 2 * pi / lambda;

% Distance between elements:

d = 0.45;

% Angle:

theta = (0 : 0.5 : 180) * pi / 180;

% Number of elements:

N = 9;

% Magnitudes of excitation:

A = ones(N, 1);

% Array factor:

AF = zeros(length(theta), 1);

for m = 1 : length(theta)

  for n = 1 : N
  
    phi = beta * d * cos(theta(m));
    
    AF(m) = AF(m) + A(n) * exp(1j * (n - 1) * phi) * sin(theta(m));
  end

end

AF = abs(AF);

maxAF = max(AF);

AF1 = AF / maxAF;

% Number of elements:

N = 19;

% Magnitudes of excitation:

A = ones(N, 1);

% Array factor:

AF = zeros(length(theta), 1);

for m = 1 : length(theta)

  for n = 1 : N
  
    phi = beta * d * cos(theta(m));
    
    AF(m) = AF(m) + A(n) * exp(1j * (n - 1) * phi) * sin(theta(m));
  end

end

AF = abs(AF);

maxAF = max(AF);

AF2 = AF / maxAF;

figure(1);

plot(theta / pi * 180, AF1, 'b-', ...
     theta / pi * 180, AF2, 'r-');