#ifndef FIXEDPNTINTEGRATOR3D_TET_H
#define FIXEDPNTINTEGRATOR3D_TET_H

#pragma once

#include "FixedPointIntegrator.h"
#include "GaussRule3D_Tet.h"
#include "R3.h"

namespace NovaIntegrator
{

    class FixedPntIntegrator3D_Tet : public FixedPointIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        NovaType::R3 m_nodes[4];

        void UpdateVertex()
        {
            for(unsigned i(0); i < NUM_VERTEX; ++i)

                m_nodes[i].Set(m_bounds + i * DIM);
        }

        virtual double ComputeJacobian(const double lc[])
        {
            NovaType::R3 r1r0(m_nodes[1]);

            r1r0.Subtract(m_nodes[0]);

            NovaType::R3 r2r0(m_nodes[2]);

            r2r0.Subtract(m_nodes[0]);

            NovaType::R3 r3r0(m_nodes[3]);

            r3r0.Subtract(m_nodes[0]);

            NovaType::R3 t;

            r1r0.Cross(r2r0, t);

            return r3r0.Dot(t);
        }

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[])
        {
            const double &L1 = lc[0];

            const double &L2 = lc[1];

            const double &L3 = lc[2];

            double L0 = 1.0 - L1 - L2 - L3;

            NovaType::R3 r(m_nodes[0]);

            r *= L0;

            r.Add(L1, m_nodes[1]);

            r.Add(L2, m_nodes[2]);

            r.Add(L3, m_nodes[3]);

            r.GetCoord(localCoord);
        }

    public:

        // Constructor:

        FixedPntIntegrator3D_Tet(const unsigned order = Integrator::DEFAULT_ORDER);

        // Destructor:

        virtual ~FixedPntIntegrator3D_Tet()
        {}

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::TET;
        }

        virtual void SetOrder(const unsigned order)
        {
//            m_order = order;

            m_rule[0] = GaussRule3D_Tet::GetInstance(order);
        }

        virtual bool IsSingularIntegrator() const
        {
            return false;
        }

        virtual bool IsAdaptiveIntegrator() const
        {
            return false;
        }

        virtual void SetBounds(const unsigned length,
                               const double *bounds)
        {
            Integrator::SetBounds(length, bounds);

            UpdateVertex();
        }

        virtual unsigned Integrate(Integrand *integrand,
                                   double* integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

    };
}

#endif // FIXEDPNTINTEGRATOR3D_TET_H
