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

        virtual ~Quad();

        // Initialize triangle mesh element:

        virtual void Initialize(const unsigned long id,
                                const NovaType::R3 **nodes);

        // Get the type of the element:

        virtual PatchType GetType()
        {
            return NovaMesh::QUAD;
        }

        virtual unsigned GetNumNodes()
        {
            return NUM_NODES;
        }

        // Given the local coordiante, compute the Jacobian:

        virtual double ComputeJacobian(const double lc[]);

        // Given the local coordinate, compute the unitary vectors:

        virtual void ComputeUnitaryVectors(const double lc[],
                                           NovaType::R3 unitary[]) const;

        // Given the local coordiante, compute the global coordiante:

        virtual void ComputeGlobalCoord(const double lc[],
                                        NovaType::R3 &gc);

        // Given the global coordinate, compute the local coordiante:

        virtual bool ComputeLocalCoord(const NovaType::R3 &gc,
                                       bool &isInside,
                                       double lc[]);
    };

}
#endif // QUAD_H
