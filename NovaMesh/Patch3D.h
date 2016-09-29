#ifndef PATCH3D_H
#define PATCH3D_H

#pragma once

#include "Patch.h"
#include "NovaDef.h"

namespace NovaMesh
{
    class Patch3D : public Patch
    {
    public:
        Patch3D() : Patch()
        {}

        virtual ~Patch3D()
        {}

        // Get the dimension of the element:

        virtual unsigned GetDimension() const
        {
            return NovaDef::DIM_3D;
        }

    };
}

#endif // PATCH3D_H
