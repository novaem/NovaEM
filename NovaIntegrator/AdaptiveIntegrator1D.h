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

        const static unsigned BOUND_REC_LENGTH;

    protected:

        virtual unsigned GetBoundRecLength() const;

        virtual unsigned GetSplitDomainNum() const;

        virtual void SplitDomain(double *oldDomain,
                                 double *newDomain,
                                 unsigned splitDirection);

    public:

        AdaptiveIntegrator1D(const unsigned order = 2);

        virtual ~AdaptiveIntegrator1D();

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::LINE;
        }

        virtual void SetOrder(const unsigned order);

        // Set number of domains.
        // This function will be used only by singular integrator.
        // By setting the number of initial domains, the domains
        // created by the singular integrator will be integrated
        // together, so will the error be evaluated together. And
        // the error estimation will be more precise:

        virtual void SetNumDomain(const unsigned numDomains);

    };
}

#endif // ADAPTIVEINTEGRATOR1D_H
