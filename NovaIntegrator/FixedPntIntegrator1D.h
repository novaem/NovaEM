#ifndef FIXEDPNTINTEGRATOR1D_H
#define FIXEDPNTINTEGRATOR1D_H

#pragma once

#include "FixedPointIntegrator.h"
#include "GaussRule1D.h"

namespace NovaIntegrator
{

    class FixedPntIntegrator1D : public FixedPointIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        virtual double ComputeJacobian(const double lc[])
        {
            return m_bounds[1] - m_bounds[0];
        }

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[])
        {
            const double &L1 = lc[0];

            double L0 = 1.0 - L1;

            localCoord[0] = m_bounds[0] * L0 + m_bounds[1] * L1;
        }

    public:

        // Constructor:

        FixedPntIntegrator1D(const unsigned order = Integrator::DEFAULT_ORDER);

        // Destructor:

        virtual ~FixedPntIntegrator1D()
        {}

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::LINE;
        }

        virtual void SetOrder(const unsigned order)
        {
            m_rule[0] = GaussRule1D::GetInstance(order);
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
#endif // FIXEDPNTINTEGRATOR1D_H
