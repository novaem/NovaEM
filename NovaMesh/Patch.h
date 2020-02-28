#ifndef PATCH_H
#define PATCH_H

#pragma once

#include <cstddef>
#include "R3.h"

namespace NovaMesh
{
    enum PatchType{LINE, TRI, QUAD, TET, HEX, PRISM};

    class Patch
    {
    protected:

        // Global ID of the element:

        unsigned long m_ID;

        // Array holds the pointers to the nodes of the element:

        const NovaType::R3 **m_nodes;

        // Center of the element:

        NovaType::R3 m_center;

    public:

        // Default constructor:

        Patch():
            m_ID(0),
            m_nodes(nullptr)
        {}

        // Destructor:

        virtual ~Patch()
        {
            if(m_nodes != nullptr)
            {
                delete[] m_nodes;

                m_nodes = nullptr;
            }
        }

        // Get the global ID of the element:

        unsigned long GetID() const
        {
            return m_ID;
        }

        // Get the array holds the pointers to the nodes of the element:

        const NovaType::R3 **GetNodes() const
        {
            return m_nodes;
        }

        // Obtain the node specified by the node ID:

        const NovaType::R3 *GetNode(unsigned nodeID) const
        {
            return m_nodes[nodeID];
        }

        // Get the center of the element:

        const NovaType::R3 &GetCenter() const
        {
            return m_center;
        }

        // Initialize the element:

        virtual void Initialize(const unsigned long id,
                                const NovaType::R3 **nodes) = 0;

        // Get the dimension of the element:

        virtual unsigned GetDimension() const = 0;

        // Get the type of the element:

        virtual PatchType GetType() const = 0;

        // Get the number of nodes:

        virtual unsigned GetNumNodes() const = 0;

        // Given the local coordiante, compute the Jacobian:

        virtual double ComputeJacobian(const double lc[]) const = 0;

        // Given the local coordinate, compute the unitary vectors:

        virtual void ComputeUnitaryVectors(const double lc[],
                                           NovaType::R3 unitary[]) const = 0;

        // Given the local coordiante, compute the global coordiante:

        virtual void ComputeGlobalCoord(const double lc[],
                                        NovaType::R3 &gc) const = 0;

        // Given the global coordinate, compute the local coordiante:

        virtual bool ComputeLocalCoord(const NovaType::R3 &gc,
                                       bool &isInside,
                                       double lc[]) const
        {
            return false;
        }

        // Compute the distance between the centers of two elements:

        virtual double ComputeDistance(const Patch &other) const
        {
            return m_center.ComputeDistance(other.GetCenter());
        }

    };
}

#endif // ELEMENT_H
