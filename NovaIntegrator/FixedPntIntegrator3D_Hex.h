#ifndef FIXEDPNTINTEGRATOR3D_HEX_H
#define FIXEDPNTINTEGRATOR3D_HEX_H


#pragma once

#include "FixedPointIntegrator.h"
#include "GaussRule1D.h"
#include "R3.h"

namespace NovaIntegrator
{

    class FixedPntIntegrator3D_Hex : public FixedPointIntegrator
    {
    public:

        const static unsigned NUM_VERTEX;

        const static unsigned DIM;

    protected:

        NovaType::R3 m_nodes[8];

        void UpdateVertex()
        {
            for(unsigned i(0); i < NUM_VERTEX; ++i)

                m_nodes[i].Set(m_bounds + i * DIM);
        }

        virtual double ComputeJacobian(const double lc[])
        {
            const double &L0 = lc[0];
            const double &L1 = lc[1];
            const double &L2 = lc[2];

            double L3 = 1.0 - L0;
            double L4 = 1.0 - L1;
            double L5 = 1.0 - L2;

            NovaType::R3 t;

            //////////////////////
            //                  //
            // Compute dR / dU: //
            //                  //
            //////////////////////

            NovaType::R3 dRdU;

            // r1 - r0:

            t.Set(m_nodes[1]);
            t.Subtract(m_nodes[0]);

            // dRdU = L4 * L5 * (r1 - r0):

            dRdU.Set(L4 * L5, t);

            // r2 - r3:

            t.Set(m_nodes[2]);
            t.Subtract(m_nodes[3]);

            // dRdU = L4 * L5 * (r1 - r0) +
            //        L1 * L5 * (r2 - r3):

            dRdU.Add(L1 * L5, t);

            // r6 - r7:

            t.Set(m_nodes[6]);
            t.Subtract(m_nodes[7]);

            // dRdU = L4 * L5 * (r1 - r0) +
            //        L1 * L5 * (r2 - r3) +
            //        L1 * L2 * (r6 - r7):

            dRdU.Add(L1 * L2, t);

            // r5 - r4:

            t.Set(m_nodes[5]);
            t.Subtract(m_nodes[4]);

            // dRdU = L4 * L5 * (r1 - r0) +
            //        L1 * L5 * (r2 - r3) +
            //        L1 * L2 * (r6 - r7) +
            //        L4 * L2 * (r5 - r4):

            dRdU.Add(L4 * L2, t);

            //////////////////////
            //                  //
            // Compute dR / dV: //
            //                  //
            //////////////////////

            NovaType::R3 dRdV;

            // r3 - r0:

            t.Set(m_nodes[3]);
            t.Subtract(m_nodes[0]);

            // dRdV = L3 * L5 * (r3 - r0):

            dRdV.Set(L3 * L5, t);

            // r2 - r1:

            t.Set(m_nodes[2]);
            t.Subtract(m_nodes[1]);

            // dRdV = L3 * L5 * (r3 - r0) +
            //        L0 * L5 * (r2 - r1):

            dRdV.Add(L0 * L5, t);

            // r6 - r5:

            t.Set(m_nodes[6]);
            t.Subtract(m_nodes[5]);

            // dRdV = L3 * L5 * (r3 - r0) +
            //        L0 * L5 * (r2 - r1) +
            //        L0 * L2 * (r6 - r5):

            dRdV.Add(L0 * L2, t);

            // r7 - r4:

            t.Set(m_nodes[7]);
            t.Subtract(m_nodes[4]);

            // dRdV = L3 * L5 * (r3 - r0) +
            //        L0 * L5 * (r2 - r1) +
            //        L0 * L2 * (r6 - r5) +
            //        L3 * L2 * (r7 - r4):

            dRdV.Add(L3 * L2, t);

            //////////////////////
            //                  //
            // Compute dR / dW: //
            //                  //
            //////////////////////

            NovaType::R3 dRdW;

            // r4 - r0:

            t.Set(m_nodes[4]);
            t.Subtract(m_nodes[0]);

            // dRdW = L3 * L4 * (r4 - r0):

            dRdW.Set(L3 * L4, t);

            // r5 - r1:

            t.Set(m_nodes[5]);
            t.Subtract(m_nodes[1]);

            // dRdW = L3 * L4 * (r4 - r0) +
            //        L0 * L4 * (r5 - r1):

            dRdW.Add(L0 * L4, t);

            // r6 - r2:

            t.Set(m_nodes[6]);
            t.Subtract(m_nodes[2]);

            // dRdW = L3 * L4 * (r4 - r0) +
            //        L0 * L4 * (r5 - r1) +
            //        L0 * L1 * (r6 - r2):

            dRdW.Add(L0 * L1, t);

            // r7 - r3:

            t.Set(m_nodes[7]);
            t.Subtract(m_nodes[3]);

            // dRdW = L3 * L4 * (r4 - r0) +
            //        L0 * L4 * (r5 - r1) +
            //        L0 * L1 * (r6 - r2) +
            //        L3 * L1 * (r7 - r3):

            dRdW.Add(L3 * L1, t);

            dRdU.Cross(dRdV, t);

            return dRdW.Dot(t);
        }

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[])
        {
            const double &L0 = lc[0];
            const double &L1 = lc[1];
            const double &L2 = lc[2];

            double L3 = 1.0 - L0;
            double L4 = 1.0 - L1;
            double L5 = 1.0 - L2;

            NovaType::R3 gc(m_nodes[0]);

            gc *= L3 * L4 * L5;

            gc.Add(L0 * L4 * L5, m_nodes[1]);

            gc.Add(L0 * L1 * L5, m_nodes[2]);

            gc.Add(L3 * L1 * L5, m_nodes[3]);

            gc.Add(L3 * L4 * L2, m_nodes[4]);

            gc.Add(L0 * L4 * L2, m_nodes[5]);

            gc.Add(L0 * L1 * L2, m_nodes[6]);

            gc.Add(L3 * L1 * L2, m_nodes[7]);

            gc.GetCoord(localCoord);

        }

    public:

        // Constructor:

        FixedPntIntegrator3D_Hex(const unsigned order = Integrator::DEFAULT_ORDER);

        // Destructor:

        virtual ~FixedPntIntegrator3D_Hex()
        {}

        virtual NovaMesh::PatchType GetSupportedMeshType() const
        {
            return NovaMesh::QUAD;
        }

        virtual void SetOrder(const unsigned order)
        {
            m_rule[0] = GaussRule1D::GetInstance(order);

            m_rule[1] = GaussRule1D::GetInstance(order);

            m_rule[2] = GaussRule1D::GetInstance(order);
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


#endif // FIXEDPNTINTEGRATOR3D_HEX_H
