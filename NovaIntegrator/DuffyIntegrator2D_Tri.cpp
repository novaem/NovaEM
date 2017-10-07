#include "AdaptiveIntegrator2D_Quad.h"
#include "DuffyIntegrator2D_Tri.h"

using namespace NovaIntegrator;

const unsigned
DuffyIntegrator2D_Tri::NUM_VERTEX = 3;

const unsigned
DuffyIntegrator2D_Tri::DIM = NovaDef::DIM_2D;

const unsigned
DuffyIntegrator2D_Tri::NUM_DOMAIN = 3;

DuffyIntegrator2D_Tri::
DuffyIntegrator2D_Tri() : DuffyIntegrator2D()
{
    InitializeBoundSpace(NUM_VERTEX * DIM);

    m_bounds[0] = 0.0;
    m_bounds[1] = 0.0;

    m_bounds[2] = 1.0;
    m_bounds[3] = 0.0;

    m_bounds[4] = 0.0;
    m_bounds[5] = 1.0;

    m_integrator->SetNumDomain(NUM_DOMAIN);
}

void DuffyIntegrator2D_Tri::
SplitDomain()
{
    double workspace[NUM_DOMAIN * BOUND_REC_LENGTH];

    double *bounds = workspace;

    double &L1 = m_singularPnt[0];

    double &L2 = m_singularPnt[1];

    bounds[0] = L1;
    bounds[1] = L2;

    bounds[2] = m_bounds[0];
    bounds[3] = m_bounds[1];

    bounds[4] = m_bounds[2];
    bounds[5] = m_bounds[3];

    bounds[6] = L1;
    bounds[7] = L2;

    bounds += BOUND_REC_LENGTH;

    bounds[0] = L1;
    bounds[1] = L2;

    bounds[2] = m_bounds[2];
    bounds[3] = m_bounds[3];

    bounds[4] = m_bounds[4];
    bounds[5] = m_bounds[5];

    bounds[6] = L1;
    bounds[7] = L2;

    bounds += BOUND_REC_LENGTH;

    bounds[0] = L1;
    bounds[1] = L2;

    bounds[2] = m_bounds[4];
    bounds[3] = m_bounds[5];

    bounds[4] = m_bounds[0];
    bounds[5] = m_bounds[1];

    bounds[6] = L1;
    bounds[7] = L2;

    m_integrator->SetBounds(NUM_DOMAIN * BOUND_REC_LENGTH,
                            workspace);

}
