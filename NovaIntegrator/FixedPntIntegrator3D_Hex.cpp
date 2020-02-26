#include "FixedPntIntegrator3D_Hex.h"

const unsigned
NovaIntegrator::FixedPntIntegrator3D_Hex::NUM_VERTEX = 8;

const unsigned
NovaIntegrator::FixedPntIntegrator3D_Hex::DIM = NovaDef::DIM_3D;


NovaIntegrator::FixedPntIntegrator3D_Hex::
FixedPntIntegrator3D_Hex(const unsigned order)
{
    InitializeRule(3);

    SetOrder(order);

    InitializeBoundSpace(NUM_VERTEX * DIM);

    m_bounds[0] = 0.0;
    m_bounds[1] = 0.0;
    m_bounds[2] = 0.0;

    m_bounds[3] = 1.0;
    m_bounds[4] = 0.0;
    m_bounds[5] = 0.0;

    m_bounds[6] = 1.0;
    m_bounds[7] = 1.0;
    m_bounds[8] = 0.0;

    m_bounds[9] = 0.0;
    m_bounds[10] = 1.0;
    m_bounds[11] = 0.0;

    m_bounds[12] = 0.0;
    m_bounds[13] = 0.0;
    m_bounds[14] = 1.0;

    m_bounds[15] = 1.0;
    m_bounds[16] = 0.0;
    m_bounds[17] = 1.0;

    m_bounds[18] = 1.0;
    m_bounds[19] = 1.0;
    m_bounds[20] = 1.0;

    m_bounds[21] = 0.0;
    m_bounds[22] = 1.0;
    m_bounds[23] = 1.0;

    UpdateVertex();
}

unsigned NovaIntegrator::FixedPntIntegrator3D_Hex::
Integrate(Integrand &integrand,
          double* integrandVector,
          const unsigned vectorLength,
          const unsigned dataType)
{
    unsigned length = vectorLength * dataType;

    InitializeWorkspace(length);

    for(unsigned i(0); i < length; ++i)

        integrandVector[i] = 0.0;

    const double *a0(NULL), *w0(NULL);

    const unsigned n0 = m_rule[0]->GetRule(a0, w0);

    const double *a1(NULL), *w1(NULL);

    const unsigned n1 = m_rule[1]->GetRule(a1, w1);

    const double *a2(NULL), *w2(NULL);

    const unsigned n2 = m_rule[2]->GetRule(a2, w2);

    double lc[NovaDef::DIM_3D] = {0.0, 0.0, 0.0};

    double localCoord[NovaDef::DIM_3D] = {0.0, 0.0, 0.0};

    double weight(0.0), weight0(0.0), weight1(0.0);

    for(unsigned i(0); i < n0; ++i)
    {
        weight0 = w0[i];

        lc[0] = a0[i];

        for(unsigned j(0); j < n1; ++j)
        {

            lc[1] = a1[j];

            weight1 = weight0 * w1[j];

            for(unsigned k(0); k < n2; ++k)
            {
                lc[2] = a2[k];

                weight = weight1 * w2[k];

                weight *= ComputeJacobian(lc);

                ComputeLocalCoordinate(lc, localCoord);

                integrand(localCoord,
                          m_workspace,
                          vectorLength,
                          dataType);

                for(unsigned m(0); m < length; ++m)

                    integrandVector[m] += m_workspace[m] * weight;
            }
        }

    }

    m_numFuncEval = vectorLength * n0 * n1 * n2;

    return 0;
}


