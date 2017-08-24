#include "AdaptiveIntegrator1D.h"

const unsigned
NovaIntegrator::AdaptiveIntegrator1D::NUM_VERTEX = 2;

const unsigned
NovaIntegrator::AdaptiveIntegrator1D::DIM = NovaDef::DIM_1D;

NovaIntegrator::AdaptiveIntegrator1D::SetNumDomain(unsigned numDomain)
{
    m_numDomains = numDomain;

    unsigned length = numDomain * NUM_VERTEX;

    InitializeBoundSpace(length);
}

NovaIntegrator::AdaptiveIntegrator1D::AdaptiveIntegrator1D()
{

}
