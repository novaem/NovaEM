#include "Triangle.h"

const unsigned NovaMesh::Triangle::NUM_NODES = 3;

NovaMesh::Triangle::Triangle():
    Patch2D(),
    m_jacobian(0.0)
{
    m_nodes = new const NovaType::R3 *[NUM_NODES];
}

// Given the local coordiante, compute the Jacobian:

double NovaMesh::Triangle::
ComputeJacobian(const double lc[])
{
    return m_jacobian;
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
