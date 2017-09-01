#include "GaussRule1D.h"
#include "FixedPntIntegrator1D.h"
#include "AdaptiveIntegrator1D.h"
using namespace NovaIntegrator;

const unsigned
AdaptiveIntegrator1D::NUM_VERTEX = 2;

const unsigned
AdaptiveIntegrator1D::DIM = NovaDef::DIM_1D;

const unsigned
AdaptiveIntegrator1D::BOUND_REC_LENGTH = AdaptiveIntegrator1D::NUM_VERTEX *
                                         AdaptiveIntegrator1D::DIM;

AdaptiveIntegrator1D::
AdaptiveIntegrator1D(const unsigned order) : AdaptiveIntegrator()
{
    InitializeRule(2);

    m_rule[0] = GaussRule1D::GetInstance(order);

    m_rule[1] = GaussRule1D::GetNextOrderInstance(order);

    m_fixedPntIntegrator = new FixedPntIntegrator1D;

    m_numDomains = 1;

    unsigned length = NUM_VERTEX;

    InitializeBoundSpace(length);
}

AdaptiveIntegrator1D::~AdaptiveIntegrator1D()
{
}

void AdaptiveIntegrator1D::SetNumDomain(unsigned numDomain)
{
    m_numDomains = numDomain;

    unsigned length = numDomain * NUM_VERTEX;

    InitializeBoundSpace(length);
}

void AdaptiveIntegrator1D::SetOrder(const unsigned order)
{
    m_rule[0] = GaussRule1D::GetInstance(order);

    m_rule[1] = GaussRule1D::GetNextOrderInstance(order);
}

unsigned AdaptiveIntegrator1D::GetBoundRecLength() const
{
    return BOUND_REC_LENGTH;
}

unsigned AdaptiveIntegrator1D::GetSplitDomainNum() const
{
    return 2;
}

void AdaptiveIntegrator1D::
SplitDomain(double *oldDomain,
            double *newDomain,
            unsigned splitDirection)
{
    double &left = oldDomain[0];

    double &right = oldDomain[1];

    double mid = left;

    mid += right;

    mid /= 2.0;

    newDomain[0] = left;

    newDomain[1] = mid;

    newDomain[2] = mid;

    newDomain[3] = right;
}
