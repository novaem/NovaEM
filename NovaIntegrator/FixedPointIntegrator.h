#ifndef FIXEDPOINTINTEGRATOR_H
#define FIXEDPOINTINTEGRATOR_H

#pragma once

#include "Integrator.h"

namespace NovaIntegrator
{

    class FixedPointIntegrator : public Integrator
    {
    protected:

        IntegrationRule **m_rule;

        virtual double ComputeJacobian(const double lc[]) = 0;

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[]) = 0;

        void CleanUp()
        {
            if(m_rule != NULL)
            {
                delete[] m_rule;

                m_rule = NULL;
            }
        }

        void InitializeRule(const unsigned numRule)
        {
            CleanUp();

            m_rule = new IntegrationRule *[numRule];
        }

    public:

        // Default constructor:

        FixedPointIntegrator();

        // Destructor:

        virtual ~FixedPointIntegrator()
        {
            CleanUp();
        }

        void SetRule(IntegrationRule *rule,
                     const unsigned ruleNo = 0)
        {
            m_rule[ruleNo] = rule;
        }

    };
}

#endif // FIXEDPOINTINTEGRATOR_H
