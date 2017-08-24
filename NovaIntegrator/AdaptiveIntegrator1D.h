#ifndef ADAPTIVEINTEGRATOR1D_H
#define ADAPTIVEINTEGRATOR1D_H

#pragma once

#include "AdaptiveIntegrator.h"

namespace NovaIntegrator
{
    class AdaptiveIntegrator1D : public AdaptiveIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        virtual double ComputeJacobian(const double lc[]);

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[]);

        virtual void SplitDomain(double *oldDomain,
                                 double *newDomain,
                                 unsigned splitDirection = 0);

    public:

        AdaptiveIntegrator1D();

        // Set number of domains.
        // This function will be used only by singular integrator.
        // By setting the number of initial domains, the domains
        // created by the singular integrator will be integrated
        // together, so will the error be evaluated together. And
        // the error estimation will be more precise:

        virtual void SetNumDomain(const unsigned numDomains);

        virtual unsigned Integrate(Integrand *integrand,
                                   double* integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);
    };
}

#endif // ADAPTIVEINTEGRATOR1D_H
