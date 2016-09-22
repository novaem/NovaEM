#ifndef QUAD_H
#define QUAD_H

#pragma once

#include "Patch2D.h"

namespace NovaMesh
{

    class Quad : public Patch2D
    {
    public:

        static const unsigned NUM_NODES;

    protected:

    public:

        Quad();

        virtual ~Quad()
        {}

        // Get the type of the element:

        virtual PatchType GetType() const
        {
            return NovaMesh::QUAD;
        }

        virtual unsigned GetNumNodes() const
        {
            return NUM_NODES;
        }

        // Initialize quad mesh element:

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

        // Given the global coordinate, compute the local coordiante:

        virtual bool ComputeLocalCoord(const NovaType::R3 &gc,
                                       bool &isInside,
                                       double lc[]) const;

        virtual void ComputeNormalDir(const double lc[],
                                      NovaType::R3 &nHat) const;
    };

}
#endif // QUAD_H
