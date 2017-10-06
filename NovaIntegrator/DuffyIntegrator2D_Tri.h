#ifndef DUFFYINTEGRATOR2D_TRI_H
#define DUFFYINTEGRATOR2D_TRI_H


#pragma once

#include "DuffyIntegrator.h"

namespace NovaIntegrator
{

    class DuffyIntegrator2D_Tri : public DuffyIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

        const static unsigned BOUND_REC_LENGTH;

        const static unsigned NUM_DOMAIN;

    protected:

        // Error tolerance:

        void CleanUp()
        {}

        virtual void SplitDomain();

    public:

        // Default constructor:

        DuffyIntegrator2D_Tri();

        // Destructor:

        virtual ~DuffyIntegrator2D_Tri()
        {
            CleanUp();
        }

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::TRI;
        }

    };
}


#endif // DUFFYINTEGRATOR2D_TRI_H
