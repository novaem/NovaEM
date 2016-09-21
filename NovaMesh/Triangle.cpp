#include "Triangle.h"

const unsigned NovaMesh::Triangle::NUM_NODES = 3;

NovaMesh::Triangle::Triangle():
    Patch2D(),
    m_jacobian(0.0)
{
    m_nodes = new const NovaType::R3 *[NUM_NODES];
}

// Initialize triangle mesh element:

void NovaMesh::Triangle::
Initialize(const unsigned long id,
           const NovaType::R3 **nodes)
{
    m_ID = id;

    for(unsigned i(0); i < NUM_NODES; ++i)

        m_nodes[i] = nodes[i];

    // r1 - r0:

    m_unitaryVec[0].Initialize(*nodes[1]);

    m_unitaryVec[0].Subtract(*nodes[0]);

    // r2 - r0:

    m_unitaryVec[1].Initialize(*nodes[2]);

    m_unitaryVec[1].Subtract(*nodes[0]);

    // Jacobian = |(r1 - r0) x (r2 - r0)|:

    NovaType::R3 n;

    m_unitaryVec[0].Cross(m_unitaryVec[1], n);

    m_jacobian = n.Mag();

}

// Given the local coordiante, compute the Jacobian:

double NovaMesh::Triangle::
ComputeJacobian(const double lc[])
{
    return m_jacobian;
}

void NovaMesh::Triangle::
ComputeUnitaryVectors(const double lc[], NovaType::R3 unitary[]) const
{
    unitary[0].Initialize(m_unitaryVec[0]);

    unitary[1].Initialize(m_unitaryVec[1]);
}

// Given the local coordiante, compute the global coordiante:

void NovaMesh::Triangle::
ComputeGlobalCoord(const double lc[],
                   NovaType::R3 &gc)
{
    const double &L1 = lc[0];

    const double &L2 = lc[1];

    double L0 = 1.0 - L1 - L2;

    gc.Initialize(L0, *m_nodes[0]);

    gc.Add(L1, *m_nodes[1]);

    gc.Add(L2, *m_nodes[2]);

}

// Given the global coordinate, compute the local coordiante:

bool NovaMesh::Triangle::
ComputeLocalCoord(const NovaType::R3 &gc,
                  bool &isInside,
                  double lc[])
{
    return false;
}
