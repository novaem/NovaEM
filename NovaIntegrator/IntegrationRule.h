#ifndef INTEGRATIONRULE_H
#define INTEGRATIONRULE_H

#pragma once

#include "Patch.h"

namespace NovaIntegrator
{
    class IntegrationRule
    {
    protected:

        unsigned m_numAbscissas;

        const double *m_abscissas;

        const double *m_weights;

        // Set the order of the rule:

        virtual void SetOrder(const unsigned order) = 0;

    public:

        // Default constructor:

        IntegrationRule():
            m_numAbscissas(0),
            m_abscissas(NULL),
            m_weights(NULL)
        {}

        // Destructor:

        virtual ~IntegrationRule()
        {}

        // Get the integration rule:

        virtual unsigned GetRule(const double *&abscissas,
                                 const double *&weights)
        {
            abscissas = m_abscissas;

            weights = m_weights;

            return m_numAbscissas;
        }

        // Get the dimension of the rule:

        virtual unsigned GetDimension() const = 0;

    };

}

#endif
