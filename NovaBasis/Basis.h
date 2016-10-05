#ifndef BASIS_H
#define BASIS_H

#pragma once

#include "Patch.h"

namespace NovaBasis
{

    class Basis
    {
    public:

        // Default constructor:

        Basis()
        {}

        // Destructor:

        virtual ~Basis()
        {}

        // Compute the value of one basis function:

        virtual void ComputeBn(const unsigned index,
                               const double lc[],
                               double *value) = 0;

//        // Compute the values of a set of basis functions:

//        virtual void ComputeBn(const double lc[],
//                               double *value) = 0;

        // Get the type of mesh element supported by basis function:

        virtual NovaMesh::PatchType GetSupportedMeshType() const = 0;

        // Get the order of the basis function:

        virtual unsigned GetOrder() const = 0;
    };

    class DivConformingBasis : public Basis
    {
    public:

        // Default constructor:

        DivConformingBasis() : Basis()
        {}

        // Destructor:

        virtual ~DivConformingBasis()
        {}

        // Compute the divergence of one basis function:

        virtual void ComputeDiv(const unsigned index,
                                const double lc[],
                                double *value) = 0;

//        // Compute the divergences of a set of basis functions:

//        virtual void ComputeDiv(const double lc[],
//                                double *value) = 0;
    };
}

#endif // BASIS_H
