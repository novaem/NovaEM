#ifndef PATCH2D_H
#define PATCH2D_H

#pragma once

#include "Patch.h"
#include "NovaDef.h"

namespace NovaMesh
{
    class Patch2D : public Patch
    {
    public:

        Patch2D() :
            Patch()
        {}

        virtual ~Patch2D()
        {}

        // Get the dimension of the element:

        virtual unsigned GetDimension() const
        {
            return NovaDef::DIM_2D;
        }

        virtual void ComputeNormalDir(const double lc[],
                                      NovaType::R3 &nHat) const= 0;

    };
}

#endif // ELEMENT2D_H
