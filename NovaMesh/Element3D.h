#ifndef ELEMENT3D_H
#define ELEMENT3D_H

#pragma once

#include "Element.h"

namespace NovaMesh
{
    class Element3D : public Element
    {
    public:
        Element3D() : Element()
        {}

        virtual ~Element3D()
        {}

        // Get the dimension of the element:

        virtual unsigned GetDimension()
        {
            return 3;
        }

    };
}

#endif // ELEMENT3D_H
