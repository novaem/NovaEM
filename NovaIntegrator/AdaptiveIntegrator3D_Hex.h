#ifndef ADAPTIVEINTEGRATOR3DHEX_H
#define ADAPTIVEINTEGRATOR3DHEX_H

#pragma once

#include "AdaptiveIntegrator.h"

namespace NovaIntegrator
{
    class AdaptiveIntegrator3D_Hex : public AdaptiveIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

        const static unsigned BOUND_REC_LENGTH;

    protected:

        virtual unsigned GetBoundRecLength() const;

        virtual unsigned GetSplitDomainNum() const;

        virtual void SplitDomain(double *oldDomain,
                                 double *newDomain,
                                 unsigned splitDirection = 0);

    public:

        AdaptiveIntegrator3D_Hex(const unsigned order = 2);

        virtual ~AdaptiveIntegrator3D_Hex();

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::HEX;
        }

        virtual void SetOrder(const unsigned order);

        // Set number of domains.
        // This function will be used only by singular integrator.
        // By setting the number of initial domains, the domains
        // created by the singular integrator will be integrated
        // together, so will the error be evaluated together. And
        // the error estimation will be more precise:

        virtual void SetNumDomain(const unsigned numDomains);

        virtual unsigned Integrate(Integrand *integrand,
                                   double *integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

    };
}

#endif // ADAPTIVEINTEGRATOR3DTET_H
