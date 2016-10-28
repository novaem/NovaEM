#ifndef FIXEDPNTINTEGRATOR2D_TRI_H
#define FIXEDPNTINTEGRATOR2D_TRI_H

#pragma once

#include "FixedPointIntegrator.h"
#include "GaussRule2D_Tri.h"

namespace NovaIntegrator
{

    class FixedPntIntegrator2D_Tri : public FixedPointIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        virtual double ComputeJacobian(const double lc[])
        {
            return (m_bounds[2] - m_bounds[0]) *
                   (m_bounds[5] - m_bounds[1]) -
                   (m_bounds[4] - m_bounds[0]) *
                   (m_bounds[3] - m_bounds[1]);
        }

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[])
        {
            const double &L1 = lc[0];

            const double &L2 = lc[1];

            double L0 = 1.0 - L1 - L2;

            localCoord[0] = m_bounds[0] * L0 +
                            m_bounds[2] * L1 +
                            m_bounds[4] * L2;

            localCoord[1] = m_bounds[1] * L0 +
                            m_bounds[3] * L1 +
                            m_bounds[5] * L2;
        }

    public:

        // Constructor:

        FixedPntIntegrator2D_Tri(const unsigned order = Integrator::DEFAULT_ORDER);

        // Destructor:

        virtual ~FixedPntIntegrator2D_Tri()
        {}

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::TRI;
        }

        virtual void SetOrder(const unsigned order)
        {
            m_order = order;

            m_rule[0] = GaussRule2D_Tri::GetInstance(order);
        }

        virtual bool IsSingularIntegrator() const
        {
            return false;
        }

        virtual bool IsAdaptiveIntegrator() const
        {
            return false;
        }

        virtual unsigned Integrate(Integrand *integrand,
                                   double* integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

    };
}

#endif // FIXEDPNTINTEGRATOR2D_TRI_H
