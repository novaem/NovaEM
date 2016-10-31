#include "FixedPntIntegrator3D_Tet.h"

const unsigned
NovaIntegrator::FixedPntIntegrator3D_Tet::NUM_VERTEX = 4;

const unsigned
NovaIntegrator::FixedPntIntegrator3D_Tet::DIM = NovaDef::DIM_3D;


NovaIntegrator::FixedPntIntegrator3D_Tet::
FixedPntIntegrator3D_Tet(const unsigned order)
{
    InitializeRule(1);

    SetOrder(order);

    InitializeBounds(NUM_VERTEX * DIM);

    m_bounds[0] = 0.0;
    m_bounds[1] = 0.0;
    m_bounds[2] = 0.0;

    m_bounds[3] = 1.0;
    m_bounds[4] = 0.0;
    m_bounds[5] = 0.0;

    m_bounds[6] = 0.0;
    m_bounds[7] = 1.0;
    m_bounds[8] = 0.0;

    m_bounds[9] = 0.0;
    m_bounds[10] = 0.0;
    m_bounds[11] = 1.0;
}

unsigned NovaIntegrator::FixedPntIntegrator3D_Tet::
Integrate(Integrand *integrand,
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

        (*integrand)(localCoord,
                     m_workspace,
                     vectorLength,
                     dataType);

        for(unsigned j(0); j < length; ++j)

            integrandVector[j] += m_workspace[j] * weight;

    }

    m_numFuncEval = vectorLength * n;

    return 0;
}


