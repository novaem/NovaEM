#include "FixedPntIntegrator2D_Quad.h"

const unsigned
NovaIntegrator::FixedPntIntegrator2D_Quad::NUM_VERTEX = 4;

const unsigned
NovaIntegrator::FixedPntIntegrator2D_Quad::DIM = NovaDef::DIM_2D;


NovaIntegrator::FixedPntIntegrator2D_Quad::
FixedPntIntegrator2D_Quad(const unsigned order)
{
    InitializeRule(2);

    SetOrder(order);

    InitializeBoundSpace(NUM_VERTEX * DIM);

    m_bounds[0] = 0.0;
    m_bounds[1] = 0.0;

    m_bounds[2] = 1.0;
    m_bounds[3] = 0.0;

    m_bounds[4] = 1.0;
    m_bounds[5] = 1.0;

    m_bounds[6] = 0.0;
    m_bounds[7] = 1.0;
}

unsigned NovaIntegrator::FixedPntIntegrator2D_Quad::
Integrate(Integrand *integrand,
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

    double lc[NovaDef::DIM_3D] = {0.0, 0.0, 0.0};

    double localCoord[NovaDef::DIM_3D] = {0.0, 0.0, 0.0};

    double weight(0.0), weight0(0.0);

    for(unsigned i(0); i < n0; ++i)
    {
        weight0 = w0[i];

        lc[0] = a0[i];

        for(unsigned j(0); j < n1; ++j)
        {
            weight = weight0 * w1[j];

            lc[1] = a1[j];

            weight *= ComputeJacobian(lc);

            ComputeLocalCoordinate(lc, localCoord);

            (*integrand)(localCoord,
                         m_workspace,
                         vectorLength,
                         dataType);

            for(unsigned k(0); k < length; ++k)

                integrandVector[k] += m_workspace[k] * weight;
        }

    }

    m_numFuncEval = vectorLength * n0 * n1;

    return 0;
}


