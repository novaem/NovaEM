#include "Quad.h"
#include "R3.h"

const unsigned NovaMesh::Quad::NUM_NODES = 4;

NovaMesh::Quad::Quad() : NovaMesh::Patch2D()
{
    m_nodes = new const NovaType::R3 *[NUM_NODES];
}

// Initialize quad mesh element:

void NovaMesh::Quad::
Initialize(const unsigned long id,
           const NovaType::R3 **nodes)
{
    m_ID = id;

    for(unsigned i(0); i < NUM_NODES; ++i)

        m_nodes[i] = nodes[i];

    double a = 0.25;

    m_center.Set(a, *nodes[0]);

    m_center.Add(a, *nodes[1]);

    m_center.Add(a, *nodes[2]);

    m_center.Add(a, *nodes[3]);

}

// Given the local coordiante, compute the Jacobian:

double NovaMesh::Quad::
ComputeJacobian(const double lc[]) const
{
    const double &L1 = lc[0];
    const double &L2 = lc[1];

    double L0 = 1.0 - L1;
    double L3 = 1.0 - L2;

    NovaType::R3 dRdU;

    NovaType::R3 dRdV;

    NovaType::R3 t;

    t.Set(*m_nodes[1]);
    t.Subtract(*m_nodes[0]);

    dRdU.Set(L3, t);

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[3]);

    dRdU.Add(L2, t);

    t.Set(*m_nodes[3]);
    t.Subtract(*m_nodes[0]);

    dRdV.Set(L0, t);

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[1]);

    dRdV.Add(L1, t);

    dRdU.Cross(dRdV, t);

    return t.Mag();
}

// Given the local coordinate, compute the unitary vectors:

void NovaMesh::Quad::
ComputeUnitaryVectors(const double lc[],
                      NovaType::R3 unitary[]) const
{
    const double &L1 = lc[0];
    const double &L2 = lc[1];

    double L0 = 1.0 - L1;
    double L3 = 1.0 - L2;

    NovaType::R3 &dRdU = unitary[0];

    NovaType::R3 &dRdV = unitary[1];

    NovaType::R3 t;

    t.Set(*m_nodes[1]);
    t.Subtract(*m_nodes[0]);

    dRdU.Set(L3, t);

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[3]);

    dRdU.Add(L2, t);

    t.Set(*m_nodes[3]);
    t.Subtract(*m_nodes[0]);

    dRdV.Set(L0, t);

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[1]);

    dRdV.Add(L1, t);

}

// Given the local coordiante, compute the global coordiante:

void NovaMesh::Quad::
ComputeGlobalCoord(const double lc[],
                   NovaType::R3 &gc) const
{
    const double &L1 = lc[0];
    const double &L2 = lc[1];

    double L0 = 1.0 - L1;
    double L3 = 1.0 - L2;

    gc.Set(L0*L3, *m_nodes[0]);

    gc.Add(L1*L3, *m_nodes[1]);

    gc.Add(L1*L2, *m_nodes[2]);

    gc.Add(L0*L2, *m_nodes[3]);

}

// Given the global coordinate, compute the local coordiante:

bool NovaMesh::Quad::
ComputeLocalCoord(const NovaType::R3 &gc,
                  bool &isInside,
                  double lc[]) const
{
    return false;
}

void NovaMesh::Quad::
ComputeNormalDir(const double lc[], NovaType::R3 &nHat) const
{
    const double &L1 = lc[0];
    const double &L2 = lc[1];

    double L0 = 1.0 - L1;
    double L3 = 1.0 - L2;

    NovaType::R3 dRdU;

    NovaType::R3 dRdV;

    NovaType::R3 &t = nHat;

    t.Set(*m_nodes[1]);
    t.Subtract(*m_nodes[0]);

    dRdU.Set(L3, t);

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[3]);

    dRdU.Add(L2, t);

    t.Set(*m_nodes[3]);
    t.Subtract(*m_nodes[0]);

    dRdV.Set(L0, t);

    t.Set(*m_nodes[2]);
    t.Subtract(*m_nodes[1]);

    dRdV.Add(L1, t);

    dRdU.Cross(dRdV, t);

    t.Normalize();

}

