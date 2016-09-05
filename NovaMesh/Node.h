#ifndef __NODE__
#define __NODE__

#include <cstddef>
#include "R3.h"

namespace NovaMesh
{
    class Node
    {
    protected:

        // Global ID of the node:

        unsigned long m_id;

        // Pointer to the location vector:

        const NovaType::R3 *m_r;

    public:

        // Default constructor:

        Node():
            m_id(0),
            m_r(NULL)
        {}

        Node(unsigned long id,
             const NovaType::R3 *r):
            m_id(id),
            m_r(r)
        {}

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

#endif // __NODE__
