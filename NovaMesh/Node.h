#ifndef NODE_H
#define NODE_H

#include <cstddef>
#include <vector>
#include "R3.h"

using namespace std;

namespace NovaMesh
{
    class Element;

    // TBD: the node class should be derived from the Topology class:

    class Node
    {
    protected:

        // Global ID of the node:

        unsigned long m_id;

        // Pointer to the location vector:

        const NovaType::R3 *m_r;

        // TBD: the m_owner member data needs to be moved into the base class:

        // Array of owner elements of this node:

        std::vector< const Element *> m_owner;

    public:

        // Default constructor:

        Node():
            m_id(0),
            m_r(NULL)
        {
            m_owner.clear();
        }

        Node(unsigned long id,
             const NovaType::R3 *r):
            m_id(id),
            m_r(r)
        {
            m_owner.clear();
        }

        unsigned long GetID()
        {
            return m_id;
        }

        const NovaType::R3 *GetLocVector()
        {
            return m_r;
        }

    };
}

#endif // NODE_H
