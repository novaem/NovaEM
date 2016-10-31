#ifndef FIXEDPNTINTEGRATOR3D_TET_H
#define FIXEDPNTINTEGRATOR3D_TET_H

#pragma once

#include "FixedPointIntegrator.h"
#include "GaussRule3D_Tet.h"

namespace NovaIntegrator
{

    class FixedPntIntegrator3D_Tet : public FixedPointIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        virtual double ComputeJacobian(const double lc[])
        {
            NovaType::R3 r0(m_bounds);

            NovaType::R3 r1r0(m_bounds + NovaDef::DIM_3D);

            r1r0.Subtract(r0);

            NovaType::R3 r2r0(m_bounds + NovaDef::DIM_3D * 2);

            r2r0.Subtract(r0);

            NovaType::R3 r3r0(m_bounds + NovaDef::DIM_3D * 3);

            r3r0.Subtract(r0);

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

            NovaType::R3 r0(m_bounds);

            NovaType::R3 r1(m_bounds + NovaDef::DIM_3D);

            NovaType::R3 r2(m_bounds + NovaDef::DIM_3D * 2);

            NovaType::R3 r3(m_bounds + NovaDef::DIM_3D * 3);

            r0 *= L0;

            r0.Add(L1, r1);

            r0.Add(L2, r2);

            r0.Add(L3, r3);

            r0.GetCoord(localCoord);
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
            m_order = order;

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

        virtual unsigned Integrate(Integrand *integrand,
                                   double* integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

    };
}

#endif // FIXEDPNTINTEGRATOR3D_TET_H
