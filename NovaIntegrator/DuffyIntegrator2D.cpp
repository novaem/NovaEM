#include "AdaptiveIntegrator2D_Quad.h"
#include "DuffyIntegrator2D.h"

using namespace NovaIntegrator;

const unsigned
DuffyIntegrator2D::BOUND_REC_LENGTH =
        AdaptiveIntegrator2D_Quad::BOUND_REC_LENGTH;

DuffyIntegrator2D::
DuffyIntegrator2D() : DuffyIntegrator()
{
    m_integrator = new AdaptiveIntegrator2D_Quad();

    m_integrator->SetErrTol(m_errTol);
}
