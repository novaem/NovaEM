#include "Tet.h"

const unsigned NovaMesh::Tet::NUM_NODES = 4;

NovaMesh::Tet::Tet():
    Patch3D(),
    m_jacobian(0.0)
{
    m_nodes = new const NovaType::R3 *[NUM_NODES];
}

// Initialize Tet mesh element:

void NovaMesh::Tet::
Initialize(const unsigned long id,
           const NovaType::R3 **nodes)
{
    m_ID = id;

    double a = 0.25;

    for(unsigned i(0); i < NUM_NODES; ++i)
    {

        m_nodes[i] = nodes[i];

        m_center.Add(a, *nodes[i]);

    }

    // r1 - r0:

    m_unitaryVec[0].Set(*nodes[1]);

    m_unitaryVec[0].Subtract(*nodes[0]);

    // r2 - r0:

    m_unitaryVec[1].Set(*nodes[2]);

    m_unitaryVec[1].Subtract(*nodes[0]);

    // r3 - r0:

    m_unitaryVec[2].Set(*nodes[3]);

    m_unitaryVec[2].Subtract(*nodes[0]);

    // Jacobian = (r3 - r0) .dot. ( (r1 - r0) x (r2 - r0) ):

    m_jacobian = m_unitaryVec[2].Dot(m_unitaryVec[0].Cross(m_unitaryVec[1]));
}

// Given the local coordiante, compute the Jacobian:

double NovaMesh::Tet::
ComputeJacobian(const double lc[]) const
{
    return m_jacobian;
}

void NovaMesh::Tet::
ComputeUnitaryVectors(const double lc[], NovaType::R3 unitary[]) const
{
    unitary[0].Set(m_unitaryVec[0]);

    unitary[1].Set(m_unitaryVec[1]);

    unitary[2].Set(m_unitaryVec[2]);
}

// Given the local coordiante, compute the global coordiante:

void NovaMesh::Tet::
ComputeGlobalCoord(const double lc[],
                   NovaType::R3 &gc) const
{
    const double &L1 = lc[0];

    const double &L2 = lc[1];

    const double &L3 = lc[2];

    double L0 = 1.0 - L1 - L2 - L3;

    gc.Set(L0, *m_nodes[0]);

    gc.Add(L1, *m_nodes[1]);

    gc.Add(L2, *m_nodes[2]);

    gc.Add(L3, *m_nodes[3]);

}

// Given the global coordinate, compute the local coordiante:

bool NovaMesh::Tet::
ComputeLocalCoord(const NovaType::R3 &gc,
                  bool &isInside,
                  double lc[]) const
{
    return false;
}

