#include "DivBasisQuad.h"

// Compute the value of one basis function:

void NovaBasis::DivBasisQuad::
ComputeBn(const unsigned index,
          const double lc[],
          double *value)
{
    const double &u = lc[0];

    const double &v = lc[1];

    switch(index)
    {
    case 0:
        value[0] = u;
        value[1] = 0.0;

        break;

    case 1:
        value[0] = 0.0;
        value[1] = v;

        break;

    case 2:
        value[0] = u - 1.0;
        value[1] = 0.0;

        break;

    case 3:
        value[0] = 0.0;
        value[1] = v - 1.0;

        break;

    default:
        break;
    }

}

// Compute the divergence of one basis function:

void NovaBasis::DivBasisQuad::
ComputeDiv(const unsigned index,
           const double lc[],
           double *value)
{
    value[0] = 1.0;
}
