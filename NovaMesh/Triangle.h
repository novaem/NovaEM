#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include "Patch2D.h"

namespace NovaMesh
{
    class Triangle : public Patch2D
    {
    public:

        static const unsigned NUM_NODES;

    protected:

        double m_jacobian;

    public:
        // Default constructor:

        Triangle();

        // Initialize triangle mesh element:

        void Initialize();

        // Get the type of the element:

        virtual PatchType GetType();

        // Given the local coordiante, compute the Jacobian:

        virtual double ComputeJacobian(const double lc[]);

        // Given the local coordiante, compute the global coordiante:

        virtual void ComputeGlobalCoord(const double lc[],
                                        NovaType::R3 &gc);

        // Given the global coordinate, compute the local coordiante:

        virtual bool ComputeLocalCoord(const NovaType::R3 &gc,
                                       bool &isInside,
                                       double lc[]);
    };
}

#endif // TRIANGLE_H
