#ifndef DUFFYINTEGRATOR_H
#define DUFFYINTEGRATOR_H


#pragma once

#include "AdaptiveIntegrator.h"

namespace NovaIntegrator
{

    class DuffyIntegrator : public Integrator
    {
    public:

        const static double DEFAULT_ERR_TOL;

    protected:

        // Error tolerance:

        double m_errTol;

        double m_singularPnt[NovaDef::DIM_3D];

        AdaptiveIntegrator *m_integrator;

        void CleanUp()
        {
            if(m_integrator != NULL)
            {
                delete m_integrator;

                m_integrator = NULL;
            }
        }

        virtual void SplitDomain() = 0;

    public:

        // Default constructor:

        DuffyIntegrator();

        // Destructor:

        virtual ~DuffyIntegrator()
        {
            CleanUp();
        }

        // Set the error tolerance for adaptive integrator:

        void SetErrTol(const double &errTol)
        {
            m_errTol = errTol;

            m_integrator->SetErrTol(errTol);
        }

        virtual bool IsSingularIntegrator() const
        {
            return true;
        }

        virtual bool IsAdaptiveIntegrator() const
        {
            return true;
        }

        virtual void SetSingularPnt(const double *pnt)
        {
            m_singularPnt[0] = pnt[0];

            m_singularPnt[1] = pnt[1];

            m_singularPnt[2] = pnt[2];
        }

        virtual unsigned Integrate(Integrand *integrand,
                                   double *integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

    };
}


#endif // DUFFYINTEGRATOR_H
