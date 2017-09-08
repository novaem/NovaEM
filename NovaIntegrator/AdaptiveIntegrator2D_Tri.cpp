#include "GaussRule1D.h"
#include "FixedPntIntegrator2D_Tri.h"
#include "AdaptiveIntegrator2D_Tri.h"
using namespace NovaIntegrator;

const unsigned
AdaptiveIntegrator2D_Tri::NUM_VERTEX = 3;

const unsigned
AdaptiveIntegrator2D_Tri::DIM = NovaDef::DIM_2D;

const unsigned
AdaptiveIntegrator2D_Tri::BOUND_REC_LENGTH =
        AdaptiveIntegrator2D_Tri::NUM_VERTEX *
        AdaptiveIntegrator2D_Tri::DIM;

AdaptiveIntegrator2D_Tri::
AdaptiveIntegrator2D_Tri(const unsigned order) : AdaptiveIntegrator()
{
    InitializeRule(2);

    m_rule[0] = GaussRule2D_Tri::GetInstance(order);

    m_rule[1] = GaussRule2D_Tri::GetNextOrderInstance(order);

    m_fixedPntIntegrator = new FixedPntIntegrator2D_Tri;

    m_numDomains = 1;

    unsigned length = BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

AdaptiveIntegrator2D_Tri::~AdaptiveIntegrator2D_Tri()
{
}

void AdaptiveIntegrator2D_Tri::SetNumDomain(unsigned numDomain)
{
    m_numDomains = numDomain;

    unsigned length = numDomain * BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

void AdaptiveIntegrator2D_Tri::SetOrder(const unsigned order)
{
    m_rule[0] = GaussRule2D_Tri::GetInstance(order);

    m_rule[1] = GaussRule2D_Tri::GetNextOrderInstance(order);
}

unsigned AdaptiveIntegrator2D_Tri::GetBoundRecLength() const
{
    return BOUND_REC_LENGTH;
}

unsigned AdaptiveIntegrator2D_Tri::GetSplitDomainNum() const
{
    return 4;
}

void AdaptiveIntegrator2D_Tri::
SplitDomain(double *oldDomain,
            double *newDomain,
            unsigned splitDirection)
{
    double &x0 = oldDomain[0];
    double &y0 = oldDomain[1];

    double &x1 = oldDomain[2];
    double &y1 = oldDomain[3];

    double &x2 = oldDomain[4];
    double &y2 = oldDomain[5];

    double nx0 = (x0 + x1) / 2.0;
    double ny0 = (y0 + y1) / 2.0;

    double nx1 = (x1 + x2) / 2.0;
    double ny1 = (y1 + y2) / 2.0;

    double nx2 = (x2 + x0) / 2.0;
    double ny2 = (y2 + y0) / 2.0;

    double *subDomain = newDomain;

    // Sub domain 0:

    subDomain[0] = x0;
    subDomain[1] = y0;

    subDomain[2] = nx0;
    subDomain[3] = ny0;

    subDomain[4] = nx2;
    subDomain[5] = ny2;

    subDomain += BOUND_REC_LENGTH;

    // Sub domain 1:

    subDomain[0] = x1;
    subDomain[1] = y1;

    subDomain[2] = nx1;
    subDomain[3] = ny1;

    subDomain[4] = nx0;
    subDomain[5] = ny0;

    subDomain += BOUND_REC_LENGTH;

    // Sub domain 2:

    subDomain[0] = x2;
    subDomain[1] = y2;

    subDomain[2] = nx2;
    subDomain[3] = ny2;

    subDomain[4] = nx1;
    subDomain[5] = ny1;

    subDomain += BOUND_REC_LENGTH;

    // Sub domain 3:

    subDomain[0] = nx0;
    subDomain[1] = ny0;

    subDomain[2] = nx1;
    subDomain[3] = ny1;

    subDomain[4] = nx2;
    subDomain[5] = ny2;
}
