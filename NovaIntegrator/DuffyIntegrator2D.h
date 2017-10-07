#ifndef DUFFYINTEGRATOR2D_H
#define DUFFYINTEGRATOR2D_H


#pragma once

#include "DuffyIntegrator.h"

namespace NovaIntegrator
{

    class DuffyIntegrator2D : public DuffyIntegrator
    {
    public:

        const static unsigned NUM_DOMAIN;

        const static unsigned BOUND_REC_LENGTH;

    protected:

        // Error tolerance:

        void CleanUp()
        {}

    public:

        // Default constructor:

        DuffyIntegrator2D();

        // Destructor:

        virtual ~DuffyIntegrator2D()
        {
            CleanUp();
        }
    };
}


#endif // DUFFYINTEGRATOR2D_H
