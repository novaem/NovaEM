#include "DuffyIntegrator.h"

const double NovaIntegrator::DuffyIntegrator::DEFAULT_ERR_TOL = 1e-3;

NovaIntegrator::DuffyIntegrator::
DuffyIntegrator():
    Integrator(),
    m_errTol(DEFAULT_ERR_TOL),
    m_integrator(NULL)
{}

unsigned NovaIntegrator::DuffyIntegrator::
Integrate(Integrand &integrand,
          double *integrandVector,
          const unsigned vectorLength,
          const unsigned dataType)
{
    SplitDomain();

    m_integrator->Integrate(integrand,
                            integrandVector,
                            vectorLength,
                            dataType);

    m_numFuncEval = m_integrator->GetNumFuncEval();

    return 0;
}
