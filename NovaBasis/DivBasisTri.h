#ifndef DIVBASISTRI_H
#define DIVBASISTRI_H

#pragma once

#include "Basis.h"

namespace NovaBasis
{

    class DivBasisTri : public DivConformingBasis
    {
    public:

        // Default constructor:

        DivBasisTri() : DivConformingBasis()
        {}

        // Destructor:

        virtual ~DivBasisTri()
        {}

        // Get the type of mesh element supported by basis function:

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::TRI;
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
#endif // DIVBASISTRI_H
