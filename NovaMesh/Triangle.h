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

        NovaType::R3 m_unitaryVec[NovaDef::DIM_2D];

        NovaType::R3 m_normalDir;

        double m_jacobian;

    public:
        // Default constructor:

        Triangle();

        virtual ~Triangle()
        {}

        // Get the type of the element:

        virtual PatchType GetType() const
        {
            return NovaMesh::TRI;
        }

        // Get the number of nodes on this type of patch:

        virtual unsigned GetNumNodes() const
        {
            return NUM_NODES;
        }

        // Initialize triangle mesh element:

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

#endif // TRIANGLE_H
