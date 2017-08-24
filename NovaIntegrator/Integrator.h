#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#pragma once

#include "IntegrationRule.h"
#include "Integrand.h"

namespace NovaIntegrator
{
    class Integrator
    {
    public:

        const static unsigned DEFAULT_ORDER;

    protected:

        unsigned m_order;

        unsigned m_boundsLength;

        double *m_bounds;

        unsigned m_workspaceLength;

        double *m_workspace;

        unsigned m_numFuncEval;

        void CleanUp()
        {
            m_boundsLength = 0;

            if(m_bounds != NULL)
            {
                delete[] m_bounds;

                m_bounds = NULL;
            }

            m_workspaceLength = 0;

            if(m_workspace != NULL)
            {
                delete[] m_workspace;

                m_workspace = NULL;
            }

            m_numFuncEval = 0;
        }

        void InitializeBoundSpace(const unsigned length)
        {
            if(length < m_boundsLength)

                return;

            if(m_bounds != NULL)
            {
                delete[] m_bounds;

                m_bounds = NULL;
            }

            m_bounds = new double[length];

            m_boundsLength = length;
        }

        void InitializeWorkspace(const unsigned length)
        {
            if(m_workspaceLength > length)

                return;

            if(m_workspace != NULL)
            {
                delete[] m_workspace;

                m_workspace = NULL;
            }

            m_workspace = new double[length];

            m_workspaceLength = length;
        }

    public:

        Integrator();

        virtual ~Integrator()
        {
            CleanUp();
        }

        virtual void SetBounds(const unsigned length,
                               const double *bounds)
        {
            for(unsigned i(0); i < length; ++i)

                m_bounds[i] = bounds[i];
        }

        unsigned GetNumFuncEval() const
        {
            return m_numFuncEval;
        }

        virtual NovaMesh::PatchType GetSupportedMeshType() const = 0;

        virtual void SetOrder(const unsigned order) = 0;

        virtual bool IsSingularIntegrator() const = 0;

        virtual bool IsAdaptiveIntegrator() const = 0;

        virtual unsigned Integrate(Integrand *integrand,
                                   double* integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType) = 0;

    };

}


#endif // INTEGRATOR_H
