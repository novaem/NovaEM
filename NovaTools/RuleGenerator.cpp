#include <iostream>
#include <fstream>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>

#include "RuleGenerator.h"

int main()
{
    ConvertTriangleRule("triasymq_table.txt");

    ConvertTetRule("tetraarbq_table.txt");
    return 0;
}

void ConvertTriangleRule(const char *filename)
{
    unsigned order(0);

    unsigned long numSamples(0);

    mpf_class three(3, 256),
              sqrt3(0, 256),
              oneOverSqrt3(0, 256),
              one(1, 256),
              half(0.5, 256),
              jacobian(0, 256);

    sqrt3 = sqrt(three);

    oneOverSqrt3 = one / sqrt3;

    jacobian = sqrt3 * 2;

    mpf_class x(0, 256), y(0, 256), z(0, 256), w(0, 256);

    mpf_class u(0, 256), v(0, 256), weight(0, 256);

    std::ifstream input;

    std::ofstream output;

    std::ofstream offset("triangleOffset.txt");

    input.open(filename);

    output.open("triangleAbscissas.txt");

    output.precision(15);

    unsigned long totalNumSample(0);

    for(unsigned n(0); n < 50; ++n)
    {
        input >> order >> numSamples;

        offset << totalNumSample << "," << std::endl;

        totalNumSample += numSamples;

        output << "// The abscissas of order "
               << order
               << " rule ("
               << numSamples << " points):"
               << std::endl << std::endl;

        for(unsigned long i(0); i < numSamples; ++i)
        {
            input >> x >> y >> w;

            v = (y + oneOverSqrt3) * oneOverSqrt3;

            u = (x + (one - v)) * half;

            output << u << ",    "
                   << v << ","
                   << std::endl;


        }

        output << std::endl;
    }

    input.close();

    output.close();

    offset.close();

    input.open(filename);

    output.open("triangleWeights.txt");

    output.precision(15);

    for(unsigned n(0); n < 50; ++n)
    {
        input >> order >> numSamples;

        output << "// The weights of order "
               << order
               << " rule ("
               << numSamples << " points):"
               << std::endl << std::endl;

        for(unsigned long i(0); i < numSamples; ++i)
        {
            input >> x >> y >> w;

            weight = w / jacobian;

            output << weight << ","
                   << std::endl;


        }

        output << std::endl;
    }

    input.close();

    output.close();

}

void ConvertTetRule(const char *filename)
{
    unsigned order(0);

    unsigned long numSamples(0);

    mpf_class three(3, 256),
              sqrt3(0, 256),
              oneOverSqrt3(0, 256),
              six(6, 256),
              sqrt6(0, 256),
              oneOverSqrt6(0, 256),
              one(1, 256),
              half(0.5, 256),
              quarter(0.25, 256),
              jacobian(0, 256);

    sqrt3 = sqrt(three);

    oneOverSqrt3 = one / sqrt3;

    sqrt6 = sqrt(six);

    oneOverSqrt6 = one / sqrt6;

    jacobian = 0.942809041582063 * 6.0;

    mpf_class x(0, 256), y(0, 256), z(0, 256), w(0, 256);

    mpf_class p(0, 256), q(0, 256), r(0, 256), weight(0, 256);

    std::ifstream input;

    std::ofstream output;

    std::ofstream offset("tetOffset.txt");

    input.open(filename);

    output.open("tetAbscissas.txt");

    output.precision(15);

    unsigned long totalNumSample(0);

    for(unsigned n(0); n < 15; ++n)
    {
        input >> order >> numSamples;

        offset << totalNumSample << "," << std::endl;

        totalNumSample += numSamples;

        output << "// The abscissas of order "
               << order
               << " rule ("
               << numSamples << " points):"
               << std::endl << std::endl;

        for(unsigned long i(0); i < numSamples; ++i)
        {
            input >> x >> y >> z >> w;

            r = (z * sqrt6 + one) * quarter;

            q = (y + (one - r) * oneOverSqrt3) * oneOverSqrt3;

            p = (x + (one - r - q)) * half;

            output << p << ",    "
                   << q << ",    "
                   << r << ","
                   << std::endl;


        }

        output << std::endl;
    }

    input.close();

    output.close();

    offset.close();

    input.open(filename);

    output.open("tetWeights.txt");

    output.precision(15);

    for(unsigned n(0); n < 15; ++n)
    {
        input >> order >> numSamples;

        output << "// The weights of order "
               << order
               << " rule ("
               << numSamples << " points):"
               << std::endl << std::endl;

        for(unsigned long i(0); i < numSamples; ++i)
        {
            input >> x >> y >> z >> w;

            weight = w / jacobian;

            output << weight << ","
                   << std::endl;


        }

        output << std::endl;
    }

    input.close();

    output.close();

}

