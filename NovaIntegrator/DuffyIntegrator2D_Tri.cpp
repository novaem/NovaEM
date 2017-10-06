#include "AdaptiveIntegrator2D_Tri.h"
#include "DuffyIntegrator2D_Tri.h"

using namespace NovaIntegrator;

const unsigned
DuffyIntegrator2D_Tri::NUM_VERTEX = 3;

const unsigned
DuffyIntegrator2D_Tri::DIM = NovaDef::DIM_2D;

const unsigned
DuffyIntegrator2D_Tri::NUM_DOMAIN = 3;

const unsigned
DuffyIntegrator2D_Tri::BOUND_REC_LENGTH =
        DuffyIntegrator2D_Tri::NUM_VERTEX *
        DuffyIntegrator2D_Tri::DIM;

DuffyIntegrator2D_Tri::DuffyIntegrator2D_Tri()
{
    m_integrator = new AdaptiveIntegrator2D_Tri();

    m_integrator->SetErrTol(m_errTol);
}

void DuffyIntegrator2D_Tri::
SplitDomain()
{
    double workspace[NUM_DOMAIN * BOUND_REC_LENGTH];

    double *bounds = workspace;

    double &L1 = m_singularPnt[0];

    double &L2 = m_singularPnt[1];

    bounds[0] = 0.0;
    bounds[1] = 0.0;

    bounds[2] = 1.0;
    bounds[3] = 0.0;

    bounds[4] = L1;
    bounds[5] = L2;

    bounds += BOUND_REC_LENGTH;

    bounds[0] = 1.0;
    bounds[1] = 0.0;

    bounds[2] = 1.0;
    bounds[3] = 0.0;

    bounds[4] = L1;
    bounds[5] = L2;

    bounds += BOUND_REC_LENGTH;

    bounds[0] = 1.0;
    bounds[1] = 1.0;

    bounds[2] = 0.0;
    bounds[3] = 0.0;

    bounds[4] = L1;
    bounds[5] = L2;

    m_integrator->SetBounds(NUM_DOMAIN * BOUND_REC_LENGTH,
                            workspace);

}
