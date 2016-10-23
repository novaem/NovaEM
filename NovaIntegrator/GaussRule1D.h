#ifndef GAUSSRULE1D_H
#define GAUSSRULE1D_H

#pragma once

#include "IntegrationRule.h"

namespace NovaIntegrator
{

    class GaussRule1D : public IntegrationRule
    {
    protected:

        const static unsigned DIM;

        const static double X[];

        const static double W[];

        virtual void SetOrder(const unsigned order);

        GaussRule1D() {}

        GaussRule1D(const unsigned order)
        {
            SetOrder(order);
        }

        GaussRule1D(const GaussRule1D &obj) {}

        GaussRule1D &operator =(const GaussRule1D &obj)
        {
            return *this;
        }

    public:

        unsigned GetDimension() const;

        static GaussRule1D *GetInstance(const unsigned order);

        static GaussRule1D *GetNextOrderInstance(const unsigned order);

    };

}

#endif // GAUSSRULE1D_H
