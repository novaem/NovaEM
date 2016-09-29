#ifndef HEX_H
#define HEX_H

#pragma once

#include "Patch3D.h"

namespace NovaMesh
{

    class Hex : public Patch3D
    {
    public:

        static const unsigned NUM_NODES;

    protected:

    public:

        Hex();

        virtual ~Hex()
        {}

        // Get the type of the element:

        virtual PatchType GetType() const
        {
            return NovaMesh::HEX;
        }

        virtual unsigned GetNumNodes() const
        {
            return NUM_NODES;
        }

        // Initialize Hex mesh element:

        virtual void Initialize(const unsigned long id,
                                const NovaType::R3 **nodes);

        // Given the local coordiante, compute the Jacobian:

        virtual double ComputeJacobian(const double lc[]) const;

        // Given the local coordinate, compute the unitary vectors:

        virtual void ComputeUnitaryVectors(const double lc[],
                                           NovaType::R3 unitary[]) const;

        // Given the local coordiante, compute the global coordiante:

        virtual void ComputeGlobalCoord(const double lc[],
                                        NovaType::R3 &gc) const;

    };
}

#endif // HEX_H
