#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once

#include <cstddef>
#include "R3.h"

namespace NovaMesh
{
    class Node;

    enum ElementType{LINE, TRI, QUAD, TET, HEX, PRISM};

    class Element
    {
    protected:

        // Global ID of the element:

        unsigned long m_ID;

        // Array holds the pointers to the nodes of the element:

        const Node **m_nodes;

        // Center of the element:

        NovaType::R3 m_center;

    public:

        // Default constructor:

        Element():
            m_ID(0),
            m_nodes(NULL)
        {}

        // Destructor:

        virtual ~Element()
        {
            if(m_nodes != NULL)
            {
                delete[] m_nodes;

                m_nodes = NULL;
            }
        }

        // Get the global ID of the element:

        unsigned long GetID() const
        {
            return m_ID;
        }

        // Get the array holds the pointers to the nodes of the element:

        const Node **GetNodes() const
        {
            return m_nodes;
        }

        // Obtain the node specified by the node ID:

        const Node *GetNode(unsigned nodeID) const
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
                                const Node **nodes) = 0;

        // Get the dimension of the element:

        virtual unsigned GetDimension() const = 0;

        // Get the type of the element:

        virtual ElementType GetType() const = 0;

        // Get the number of nodes:

        virtual unsigned GetNumNodes() const = 0;

        // Given the local coordiante, compute the Jacobian:

        virtual double ComputeJacobian(const double lc[]) const = 0;

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

        virtual double ComputeDistance(const Element &element) const
        {
            return m_center.ComputeDistance(element.GetCenter());
        }

    };
}

#endif // ELEMENT_H
