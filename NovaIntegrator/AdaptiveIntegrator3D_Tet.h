#ifndef ADAPTIVEINTEGRATOR3DTET_H
#define ADAPTIVEINTEGRATOR3DTET_H

#pragma once

#include "AdaptiveIntegrator.h"

namespace NovaIntegrator
{
    class AdaptiveIntegrator3D_Tet : public AdaptiveIntegrator
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

        AdaptiveIntegrator3D_Tet(const unsigned order = 2);

        virtual ~AdaptiveIntegrator3D_Tet();

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::TET;
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

#endif // ADAPTIVEINTEGRATOR3DTET_H
