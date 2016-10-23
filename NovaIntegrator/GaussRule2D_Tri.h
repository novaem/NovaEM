#ifndef GAUSSRULE2D_TRI_H
#define GAUSSRULE2D_TRI_H

#pragma once

#include "IntegrationRule.h"

namespace NovaIntegrator
{

    class GaussRule2D_Tri : public IntegrationRule
    {
    protected:

        const static unsigned DIM;
        const static unsigned OFFSET[];

        const static double X[];

        const static double W[];

        virtual void SetOrder(const unsigned order);

        GaussRule2D_Tri() {}

        GaussRule2D_Tri(const unsigned order)
        {
            SetOrder(order);
        }

        GaussRule2D_Tri(const GaussRule2D_Tri &obj) {}

        GaussRule2D_Tri &operator =(const GaussRule2D_Tri &obj)
        {
            return *this;
        }

    public:

        unsigned GetDimension() const;

        static GaussRule2D_Tri *GetInstance(const unsigned order);

        static GaussRule2D_Tri *GetNextOrderInstance(const unsigned order);

    };

}


#endif // GAUSSRULE2D_TRI_H
