#ifndef DUFFYINTEGRATOR2D_QUAD_H
#define DUFFYINTEGRATOR2D_QUAD_H


#pragma once

#include "DuffyIntegrator2D.h"

namespace NovaIntegrator
{

    class DuffyIntegrator2D_Quad : public DuffyIntegrator2D
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

        const static unsigned NUM_DOMAIN;

    protected:

        // Error tolerance:

        void CleanUp()
        {}

        virtual void SplitDomain();

    public:

        // Default constructor:

        DuffyIntegrator2D_Quad();

        // Destructor:

        virtual ~DuffyIntegrator2D_Quad()
        {
            CleanUp();
        }

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::QUAD;
        }

    };
}


#endif // DUFFYINTEGRATOR2D_QUAD_H
