#ifndef FIXEDPNTINTEGRATOR2D_QUAD_H
#define FIXEDPNTINTEGRATOR2D_QUAD_H


#pragma once

#include "FixedPointIntegrator.h"
#include "GaussRule1D.h"

namespace NovaIntegrator
{

    class FixedPntIntegrator2D_Quad : public FixedPointIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        virtual double ComputeJacobian(const double lc[])
        {
            const double &L1 = lc[0];
            const double &L2 = lc[1];

            double L0 = 1.0 - L1;
            double L3 = 1.0 - L2;

            double x1 = L3 * (m_bounds[2] - m_bounds[0]) +
                        L2 * (m_bounds[4] - m_bounds[6]);

            double y1 = L3 * (m_bounds[3] - m_bounds[1]) +
                        L2 * (m_bounds[5] - m_bounds[7]);

            double x2 = L0 * (m_bounds[6] - m_bounds[0]) +
                        L1 * (m_bounds[4] - m_bounds[2]);

            double y2 = L0 * (m_bounds[7] - m_bounds[1]) +
                        L1 * (m_bounds[5] - m_bounds[3]);

            return (x1 * y2 - x2 * y1);
        }

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[])
        {
            const double &L1 = lc[0];
            const double &L2 = lc[1];

            double L0 = 1.0 - L1;
            double L3 = 1.0 - L2;

            localCoord[0] = m_bounds[0] * L0 * L3 +
                            m_bounds[2] * L1 * L3 +
                            m_bounds[4] * L1 * L2 +
                            m_bounds[6] * L0 * L2;

            localCoord[1] = m_bounds[1] * L0 * L3 +
                            m_bounds[3] * L1 * L3 +
                            m_bounds[5] * L1 * L2 +
                            m_bounds[7] * L0 * L2;
        }

    public:

        // Constructor:

        FixedPntIntegrator2D_Quad(const unsigned order = Integrator::DEFAULT_ORDER);

        // Destructor:

        virtual ~FixedPntIntegrator2D_Quad()
        {}

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::QUAD;
        }

        virtual void SetOrder(const unsigned order)
        {
            m_rule[0] = GaussRule1D::GetInstance(order);

            m_rule[1] = GaussRule1D::GetInstance(order);
        }

        virtual bool IsSingularIntegrator() const
        {
            return false;
        }

        virtual bool IsAdaptiveIntegrator() const
        {
            return false;
        }

        virtual unsigned Integrate(Integrand &integrand,
                                   double* integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

    };
}


#endif // FIXEDPNTINTEGRATOR2D_QUAD_H
