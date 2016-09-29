#include "Hex.h"

const unsigned NovaMesh::Hex::NUM_NODES = 8;

NovaMesh::Hex::Hex() : NovaMesh::Patch3D()
{
    m_nodes = new const NovaType::R3 *[NUM_NODES];
}

// Initialize Hex mesh element:

void NovaMesh::Hex::
Initialize(const unsigned long id,
           const NovaType::R3 **nodes)
{
    m_ID = id;

    double a = 0.125;

    for(unsigned i(0); i < NUM_NODES; ++i)
    {
        m_nodes[i] = nodes[i];

        m_center.Add(a, *nodes[i]);

    }

}

// Given the local coordiante, compute the Jacobian:

double NovaMesh::Hex::
ComputeJacobian(const double lc[]) const
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

    t.Set(*m_nodes[1]);
    t.Subtract(*m_nodes[0]);

    // dRdU = L4 * L5 * (r1 - r0):

    dRdU.Set(L4 * L5, t);

    // r2 - r3:

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[3]);

    // dRdU = L4 * L5 * (r1 - r0) +
    //        L1 * L5 * (r2 - r3):

    dRdU.Add(L1 * L5, t);

    // r6 - r7:

    t.Set(*m_nodes[6]);
    t.Subtract(*m_nodes[7]);

    // dRdU = L4 * L5 * (r1 - r0) +
    //        L1 * L5 * (r2 - r3) +
    //        L1 * L2 * (r6 - r7):

    dRdU.Add(L1 * L2, t);

    // r5 - r4:

    t.Set(*m_nodes[5]);
    t.Subtract(*m_nodes[4]);

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

    t.Set(*m_nodes[3]);
    t.Subtract(*m_nodes[0]);

    // dRdV = L3 * L5 * (r3 - r0):

    dRdV.Set(L3 * L5, t);

    // r2 - r1:

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[1]);

    // dRdV = L3 * L5 * (r3 - r0) +
    //        L0 * L5 * (r2 - r1):

    dRdV.Add(L0 * L5, t);

    // r6 - r5:

    t.Set(*m_nodes[6]);
    t.Subtract(*m_nodes[5]);

    // dRdV = L3 * L5 * (r3 - r0) +
    //        L0 * L5 * (r2 - r1) +
    //        L0 * L2 * (r6 - r5):

    dRdV.Add(L0 * L2, t);

    // r7 - r4:

    t.Set(*m_nodes[7]);
    t.Subtract(*m_nodes[4]);

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

    t.Set(*m_nodes[4]);
    t.Subtract(*m_nodes[0]);

    // dRdW = L3 * L4 * (r4 - r0):

    dRdW.Set(L3 * L4, t);

    // r5 - r1:

    t.Set(*m_nodes[5]);
    t.Subtract(*m_nodes[1]);

    // dRdW = L3 * L4 * (r4 - r0) +
    //        L0 * L4 * (r5 - r1):

    dRdW.Add(L0 * L4, t);

    // r6 - r2:

    t.Set(*m_nodes[6]);
    t.Subtract(*m_nodes[2]);

    // dRdW = L3 * L4 * (r4 - r0) +
    //        L0 * L4 * (r5 - r1) +
    //        L0 * L1 * (r6 - r2):

    dRdW.Add(L0 * L1, t);

    // r7 - r3:

    t.Set(*m_nodes[7]);
    t.Subtract(*m_nodes[3]);

    // dRdW = L3 * L4 * (r4 - r0) +
    //        L0 * L4 * (r5 - r1) +
    //        L0 * L1 * (r6 - r2) +
    //        L3 * L1 * (r7 - r3):

    dRdW.Add(L3 * L1, t);

    dRdU.Cross(dRdV, t);

    return dRdW.Dot(t);
}

// Given the local coordinate, compute the unitary vectors:

void NovaMesh::Hex::
ComputeUnitaryVectors(const double lc[],
                      NovaType::R3 unitary[]) const
{
    NovaType::R3 &dRdU = unitary[0];

    NovaType::R3 &dRdV = unitary[1];

    NovaType::R3 &dRdW = unitary[2];

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

    // r1 - r0:

    t.Set(*m_nodes[1]);
    t.Subtract(*m_nodes[0]);

    // dRdU = L4 * L5 * (r1 - r0):

    dRdU.Set(L4 * L5, t);

    // r2 - r3:

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[3]);

    // dRdU = L4 * L5 * (r1 - r0) +
    //        L1 * L5 * (r2 - r3):

    dRdU.Add(L1 * L5, t);

    // r6 - r7:

    t.Set(*m_nodes[6]);
    t.Subtract(*m_nodes[7]);

    // dRdU = L4 * L5 * (r1 - r0) +
    //        L1 * L5 * (r2 - r3) +
    //        L1 * L2 * (r6 - r7):

    dRdU.Add(L1 * L2, t);

    // r5 - r4:

    t.Set(*m_nodes[5]);
    t.Subtract(*m_nodes[4]);

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

    // r3 - r0:

    t.Set(*m_nodes[3]);
    t.Subtract(*m_nodes[0]);

    // dRdV = L3 * L5 * (r3 - r0):

    dRdV.Set(L3 * L5, t);

    // r2 - r1:

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[1]);

    // dRdV = L3 * L5 * (r3 - r0) +
    //        L0 * L5 * (r2 - r1):

    dRdV.Add(L0 * L5, t);

    // r6 - r5:

    t.Set(*m_nodes[6]);
    t.Subtract(*m_nodes[5]);

    // dRdV = L3 * L5 * (r3 - r0) +
    //        L0 * L5 * (r2 - r1) +
    //        L0 * L2 * (r6 - r5):

    dRdV.Add(L0 * L2, t);

    // r7 - r4:

    t.Set(*m_nodes[7]);
    t.Subtract(*m_nodes[4]);

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

    // r4 - r0:

    t.Set(*m_nodes[4]);
    t.Subtract(*m_nodes[0]);

    // dRdW = L3 * L4 * (r4 - r0):

    dRdW.Set(L3 * L4, t);

    // r5 - r1:

    t.Set(*m_nodes[5]);
    t.Subtract(*m_nodes[1]);

    // dRdW = L3 * L4 * (r4 - r0) +
    //        L0 * L4 * (r5 - r1):

    dRdW.Add(L0 * L4, t);

    // r6 - r2:

    t.Set(*m_nodes[6]);
    t.Subtract(*m_nodes[2]);

    // dRdW = L3 * L4 * (r4 - r0) +
    //        L0 * L4 * (r5 - r1) +
    //        L0 * L1 * (r6 - r2):

    dRdW.Add(L0 * L1, t);

    // r7 - r3:

    t.Set(*m_nodes[7]);
    t.Subtract(*m_nodes[3]);

    // dRdW = L3 * L4 * (r4 - r0) +
    //        L0 * L4 * (r5 - r1) +
    //        L0 * L1 * (r6 - r2) +
    //        L3 * L1 * (r7 - r3):

    dRdW.Add(L3 * L1, t);

}

// Given the local coordiante, compute the global coordiante:

void NovaMesh::Hex::
ComputeGlobalCoord(const double lc[],
                   NovaType::R3 &gc) const
{
    const double &L0 = lc[0];
    const double &L1 = lc[1];
    const double &L2 = lc[2];

    double L3 = 1.0 - L0;
    double L4 = 1.0 - L1;
    double L5 = 1.0 - L2;

    gc.Set(L3 * L4 * L5, *m_nodes[0]);

    gc.Add(L0 * L4 * L5, *m_nodes[1]);

    gc.Add(L0 * L1 * L5, *m_nodes[2]);

    gc.Add(L3 * L1 * L5, *m_nodes[3]);

    gc.Add(L3 * L4 * L2, *m_nodes[4]);

    gc.Add(L0 * L4 * L2, *m_nodes[5]);

    gc.Add(L0 * L1 * L2, *m_nodes[6]);

    gc.Add(L3 * L1 * L2, *m_nodes[7]);

}
