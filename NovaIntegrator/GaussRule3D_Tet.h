#ifndef GAUSSRULE3D_TET_H
#define GAUSSRULE3D_TET_H

#pragma once

#include "IntegrationRule.h"

namespace NovaIntegrator
{

    class GaussRule3D_Tet : public IntegrationRule
    {
    protected:

        const static unsigned DIM;
        const static unsigned OFFSET[];

        const static double X[];

        const static double W[];

        virtual void SetOrder(const unsigned order);

        GaussRule3D_Tet() {}

        GaussRule3D_Tet(const unsigned order)
        {
            SetOrder(order);
        }

        GaussRule3D_Tet(const GaussRule3D_Tet &obj) {}

        GaussRule3D_Tet &operator =(const GaussRule3D_Tet &obj)
        {
            return *this;
        }

    public:

        unsigned GetDimension() const;

        static GaussRule3D_Tet *GetInstance(const unsigned order);

        static GaussRule3D_Tet *GetNextOrderInstance(const unsigned order);

    };

}

#endif // GAUSSRULE3D_TET_H
