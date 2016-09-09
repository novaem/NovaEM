#ifndef ELEMENT2D_H
#define ELEMENT2D_H

#pragma once

#include "Element.h"

namespace NovaMesh
{
    class Element2D : public Element
    {
    public:

        Element2D() :
            Element()
        {}

        virtual ~Element2D()
        {}

        // Get the dimension of the element:

        virtual unsigned GetDimension()
        {
            return 2;
        }

        virtual void ComputeNormalDir(const double lc[],
                                      NovaType::R3 &nHat) = 0;

    };
}

#endif // ELEMENT2D_H
