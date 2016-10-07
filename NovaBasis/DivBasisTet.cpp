#include "DivBasisTet.h"

// Compute the value of one basis function:

void NovaBasis::DivBasisTet::
ComputeBn(const unsigned index,
          const double lc[],
          double *value)
{
    const double &u = lc[0];

    const double &v = lc[1];

    const double &w = lc[2];

    switch(index)
    {
    case 0:
        value[0] = u;
        value[1] = v;
        value[3] = w;

        break;

    case 1:
        value[0] = u - 1.0;
        value[1] = v;
        value[3] = w;

        break;

    case 2:
        value[0] = u;
        value[1] = v - 1.0;
        value[3] = w;

        break;

    case 3:
        value[0] = u;
        value[1] = v;
        value[3] = w - 1.0;

    default:
        break;

    }

}

// Compute the divergence of one basis function:

void NovaBasis::DivBasisTet::
ComputeDiv(const unsigned index,
           const double lc[],
           double *value)
{
    value[0] = 3.0;
}
