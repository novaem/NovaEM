#ifndef DIVBASISTET_H
#define DIVBASISTET_H


#pragma once

#include "Basis.h"

namespace NovaBasis
{

    class DivBasisTet : public DivConformingBasis
    {
    public:

        // Default constructor:

        DivBasisTet() : DivConformingBasis()
        {}

        // Destructor:

        virtual ~DivBasisTet()
        {}

        // Get the type of mesh element supported by basis function:

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::TET;
        }

        // Get the order of the basis function:

        virtual unsigned GetOrder() const
        {
            return 1;
        }

        // Compute the value of one basis function:

        virtual void ComputeBn(const unsigned index,
                               const double lc[],
                               double *value);

        // Compute the divergence of one basis function:

        virtual void ComputeDiv(const unsigned index,
                                const double lc[],
                                double *value);
    };

}

#endif // DIVBASISTET_H
