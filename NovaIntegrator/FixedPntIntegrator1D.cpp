#include "FixedPntIntegrator1D.h"

const unsigned
NovaIntegrator::FixedPntIntegrator1D::NUM_VERTEX = 2;

const unsigned
NovaIntegrator::FixedPntIntegrator1D::DIM = NovaDef::DIM_1D;


NovaIntegrator::FixedPntIntegrator1D::
FixedPntIntegrator1D(const unsigned order)
{
    InitializeRule(1);

    SetOrder(order);

    InitializeBoundSpace(NUM_VERTEX * DIM);

    m_bounds[0] = 0.0;

    m_bounds[1] = 1.0;
}

unsigned NovaIntegrator::FixedPntIntegrator1D::
Integrate(Integrand &integrand,
          double* integrandVector,
          const unsigned vectorLength,
          const unsigned dataType)
{
    unsigned length = vectorLength * dataType;

    InitializeWorkspace(length);

    for(unsigned i(0); i < length; ++i)

        integrandVector[i] = 0.0;

    const double *a(NULL), *w(NULL);

    const unsigned n = m_rule[0]->GetRule(a, w);

    double localCoord[NovaDef::DIM_3D] = {0.0, 0.0, 0.0};

    double jacobian = ComputeJacobian(localCoord);

    double weight(0.0);

    for(unsigned i(0); i < n; ++i)
    {
        weight = w[i];

        weight *= jacobian;

        const double *lc = a + i * DIM;

        ComputeLocalCoordinate(lc, localCoord);

        integrand(localCoord,
                  m_workspace,
                  vectorLength,
                  dataType);

        for(unsigned j(0); j < length; ++j)

            integrandVector[j] += m_workspace[j] * weight;

    }

    m_numFuncEval = vectorLength * n;

    return 0;
}


