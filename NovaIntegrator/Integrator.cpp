#include "Integrator.h"

const unsigned
NovaIntegrator::Integrator::DEFAULT_ORDER = 3;

NovaIntegrator::Integrator::
Integrator():
    m_order(0),
    m_bounds(NULL),
    m_numFuncEval(0)
{

}
