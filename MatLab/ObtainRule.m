clear all;
close all;
clc;

format longG;

abscissa = fopen('lineAbscissas.txt', 'w');
weight = fopen('lineWeights.txt', 'w');
offset = fopen('lineOffset.txt', 'w');

n = 0;

format long e;

for i = 1 : 50
    
    [x, w] = lgwt(i, 0.0, 1.0);
    
    fprintf(offset, '%4d%s \r\n', n, ',');
    
    fprintf(abscissa, '// The abscissas of order %d rule', 2 * i - 1);
    fprintf(abscissa, ' (%d point(s)):\r\n\r\n', i);
    
    fprintf(weight, '// The weights of order %d rule', 2 * i - 1);
    fprintf(weight, ' (%d point(s)):\r\n\r\n', i);
    
#    fprintf(weight, '// Gaussian quadrature weight(s) of %d point(s) rule:\r\n\r\n', i);
    
    for j = i : -1 : 1
       
        fprintf(abscissa, '%1.14e%s \r\n', x(j), ',');
        
        fprintf(weight, '%1.14e%s \r\n', w(j), ',');
        
        n = n + 1;
    end
    
    fprintf(abscissa, '\r\n');
    fprintf(weight, '\r\n');
    
end 

fclose(abscissa);
fclose(weight);
fclose(offset);



