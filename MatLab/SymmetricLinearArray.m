clear all;
close all;
clc;

% Freespace wavelength:

lambda = 1;

% Freespace wave number:

beta = 2 * pi / lambda;

%% Distance between elements:
%
%d = 0.7559 * lambda;

%d = 0.45 * lambda;

% Microstrip wavelength:

lambdaMicrostrip = lambda / sqrt(1.75);

% Microstrip wave number:

betaMicrostrip = 2 * pi / lambdaMicrostrip;

% Phase difference of excitation of adjacent elements:

alpha = 2 * pi;

d = alpha / betaMicrostrip;

% Angle:

theta = (0 : 0.5 : 180) * pi / 180;

% Number of elements:

N = 9;

% Magnitudes of excitation:

A = ones(N, 1);

% Array factor:

AF = zeros(length(theta), 1);

for m = 1 : length(theta)

  AF(m) = A((N - 1) / 2 + 1) * sin(theta(m));
  
  for n = 1 : (N - 1) / 2
  
    phi = beta * d * cos(theta(m));
    
    % Right element:
    
    AF(m) = AF(m) + A(n) * exp(1j * n * (phi + alpha)) * sin(theta(m));
    
    % Left element:
    
    AF(m) = AF(m) + A(n) * exp(1j * n * (-phi + alpha)) * sin(theta(m));
    
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

  AF(m) = A((N - 1) / 2 + 1) * sin(theta(m));
  
  for n = 1 : (N - 1) / 2
  
    phi = beta * d * cos(theta(m));
    
    % Right element:
    
    AF(m) = AF(m) + A(n) * exp(1j * n * (phi + alpha)) * sin(theta(m));
    
    % Left element:
    
    AF(m) = AF(m) + A(n) * exp(1j * n * (-phi + alpha)) * sin(theta(m));
  end

end

AF = abs(AF);

maxAF = max(AF);

AF2 = AF / maxAF;

figure(1);

plot(theta / pi * 180, AF1, 'b-', ...
     theta / pi * 180, AF2, 'r-');
 
grid on;
