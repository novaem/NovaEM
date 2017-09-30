#include "GaussRule1D.h"
#include "FixedPntIntegrator1D.h"
#include "FixedPntIntegrator2D_Quad.h"
#include "AdaptiveIntegrator2D_Quad.h"
using namespace NovaIntegrator;

const unsigned
AdaptiveIntegrator2D_Quad::NUM_VERTEX = 4;

const unsigned
AdaptiveIntegrator2D_Quad::DIM = NovaDef::DIM_2D;

const unsigned
AdaptiveIntegrator2D_Quad::BOUND_REC_LENGTH =
        AdaptiveIntegrator2D_Quad::NUM_VERTEX *
        AdaptiveIntegrator2D_Quad::DIM;

AdaptiveIntegrator2D_Quad::
AdaptiveIntegrator2D_Quad(const unsigned order) : AdaptiveIntegrator()
{
    InitializeRule(2);

    m_rule[0] = GaussRule1D::GetInstance(order);

    m_rule[1] = GaussRule1D::GetNextOrderInstance(order);

    m_fixedPntIntegrator = new FixedPntIntegrator2D_Quad;

    m_numDomains = 1;

    unsigned length = BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

AdaptiveIntegrator2D_Quad::~AdaptiveIntegrator2D_Quad()
{
}

void AdaptiveIntegrator2D_Quad::SetNumDomain(unsigned numDomain)
{
    m_numDomains = numDomain;

    unsigned length = numDomain * BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

void AdaptiveIntegrator2D_Quad::SetOrder(const unsigned order)
{
    m_rule[0] = GaussRule1D::GetInstance(order);

    m_rule[1] = GaussRule1D::GetNextOrderInstance(order);
}

unsigned AdaptiveIntegrator2D_Quad::GetBoundRecLength() const
{
    return BOUND_REC_LENGTH;
}

unsigned AdaptiveIntegrator2D_Quad::GetSplitDomainNum() const
{
    return 2;
}

void AdaptiveIntegrator2D_Quad::
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

    double &x3 = oldDomain[6];
    double &y3 = oldDomain[7];

    double *subDomain = newDomain;

    if(splitDirection == 0)
    {
        double nx0 = (x0 + x1) / 2.0;
        double ny0 = (y0 + y1) / 2.0;

        double nx1 = (x3 + x2) / 2.0;
        double ny1 = (y3 + y2) / 2.0;

        // Sub domain 0:

        subDomain[0] = x0;
        subDomain[1] = y0;

        subDomain[2] = nx0;
        subDomain[3] = ny0;

        subDomain[4] = nx1;
        subDomain[5] = ny1;

        subDomain[6] = x3;
        subDomain[7] = y3;

        subDomain += BOUND_REC_LENGTH;

        // Sub domain 1:

        subDomain[0] = nx0;
        subDomain[1] = ny0;

        subDomain[2] = x1;
        subDomain[3] = y1;

        subDomain[4] = x2;
        subDomain[5] = y2;

        subDomain[6] = nx1;
        subDomain[7] = ny1;
    }

    else
    {
        double nx0 = (x0 + x3) / 2.0;
        double ny0 = (y0 + y3) / 2.0;

        double nx1 = (x1 + x2) / 2.0;
        double ny1 = (y1 + y2) / 2.0;

        // Sub domain 0:

        subDomain[0] = x0;
        subDomain[1] = y0;

        subDomain[2] = x1;
        subDomain[3] = y1;

        subDomain[4] = nx1;
        subDomain[5] = ny1;

        subDomain[6] = nx0;
        subDomain[7] = ny0;

        subDomain += BOUND_REC_LENGTH;

        // Sub domain 1:

        subDomain[0] = nx0;
        subDomain[1] = ny0;

        subDomain[2] = nx1;
        subDomain[3] = ny1;

        subDomain[4] = x2;
        subDomain[5] = y2;

        subDomain[6] = x3;
        subDomain[7] = y3;
    }
}

unsigned NovaIntegrator::AdaptiveIntegrator2D_Quad::
Integrate(Integrand *integrand,
          double *integrandVector,
          const unsigned vectorLength,
          const unsigned dataType)
{
    unsigned boundRecLength = GetBoundRecLength();

    // Allocate the space for the bounds of sub domains:

    unsigned subDomainBoundLength = MAX_NUM_SUBDOMAIN *
                                    boundRecLength;

    AllocateSubdomainBounds(subDomainBoundLength);

    double *subDomainBounds1 = m_subdomainBounds1;

    double *subDomainBounds2 = m_subdomainBounds2;

    unsigned splitDomainNum = GetSplitDomainNum();

    // Allocate the space for the results vectors:

    unsigned resultLength = vectorLength * dataType;

    unsigned numResultVec = 5;

    InitializeWorkspace(resultLength * numResultVec);

    double *globalResult1 = m_workspace;

    double *globalResult2 = globalResult1 + resultLength;

    double *resultLow = globalResult2 + resultLength;

    double *resultHigh0 = resultLow + resultLength;

    double *resultHigh1 = resultHigh0 + resultLength;

    double *resultHigh(NULL);

    // Set the fixed point integration rules:

    IntegrationRule *ruleLow = m_rule[0];

    IntegrationRule *ruleHigh = m_rule[1];

    // Estimate the integral over the entire domain:

    m_fixedPntIntegrator->SetRule(ruleLow, 0);

    m_fixedPntIntegrator->SetRule(ruleLow, 1);

    m_fixedPntIntegrator->SetBounds(boundRecLength, m_bounds);

    m_fixedPntIntegrator->Integrate(integrand,
                                    globalResult1,
                                    vectorLength,
                                    dataType);

    m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

    for(unsigned i(0); i < resultLength; ++i)

        integrandVector[i] = 0.0;

    unsigned numNewSubDomains = m_numDomains;

    subDomainBoundLength = m_numDomains * boundRecLength;

    for(unsigned i(0); i < subDomainBoundLength; ++i)

        subDomainBounds1[i] = m_bounds[i];

    unsigned numSubDomains(0);

    unsigned splitDir(0);

    double error0(0.0), error1(0.0);

    bool failed(false);

    bool isAbsErr(false);

    bool converged(false);

    double errTol = m_errTol * 0.1;

    double absErrTol = m_absErrTol * 0.1;

    double *currentSubDomain(NULL), *newSubDomain(NULL);

    while(numNewSubDomains != 0)
    {
        numSubDomains = numNewSubDomains;

        numNewSubDomains = 0;

        currentSubDomain = subDomainBounds1;

        newSubDomain = subDomainBounds2;

        for(unsigned i(0); i < numSubDomains; ++i)
        {
            // Set the bounds of the fixed point integrator
            // to be current sub domain:

            m_fixedPntIntegrator->SetBounds(boundRecLength,
                                            currentSubDomain);

            // Compute integral using lower order rule:

            m_fixedPntIntegrator->SetRule(ruleLow, 0);

            m_fixedPntIntegrator->SetRule(ruleLow, 1);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultLow,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Compute integral using higher order rule along x direction:

            m_fixedPntIntegrator->SetRule(ruleHigh, 0);

            m_fixedPntIntegrator->SetRule(ruleLow, 1);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultHigh0,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Estimate error:

            error0 = EstimateError(resultLength,
                                   globalResult1,
                                   resultLow,
                                   resultHigh0,
                                   isAbsErr);

            // Check convergence:

            if(isAbsErr)
            {
                m_absoluteErr = true;

                converged = error0 < absErrTol;
            }

            else

                converged = error0 < errTol;

            // Compute integral using higher order rule along y direction:

            m_fixedPntIntegrator->SetRule(ruleLow, 0);

            m_fixedPntIntegrator->SetRule(ruleHigh, 1);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultHigh1,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Estimate error:

            error1 = EstimateError(resultLength,
                                   globalResult1,
                                   resultLow,
                                   resultHigh1,
                                   isAbsErr);

            // Check convergence:

            if(isAbsErr)
            {
                m_absoluteErr = true;

                converged = converged && error1 < absErrTol;
            }

            else

                converged = converged && error1 < errTol;

            if(error0 < error1)
            {
                resultHigh = resultHigh0;

                splitDir = 1;
            }

            else
            {
                resultHigh = resultHigh1;

                splitDir = 0;
            }

            if(converged)

                // Add integral over current sub domain (converged)
                // to the integrand vector:

                AccumulateVector(resultLength,
                                 resultHigh,
                                 integrandVector);

            else
            {
                // Add integral of current sub domain (unconverged)
                // to the global result of current iteration:

                AccumulateVector(resultLength,
                                 resultHigh,
                                 globalResult2);

                // Split current sub domain:

                if(numNewSubDomains + splitDomainNum > MAX_NUM_SUBDOMAIN)

                    failed = true;

                else
                {
                    SplitDomain(currentSubDomain, newSubDomain, splitDir);

                    newSubDomain += splitDomainNum * boundRecLength;

                    numNewSubDomains += splitDomainNum;
                }
            }

            currentSubDomain += boundRecLength;

        }

        // Add integral over converged sub domains to the
        // global result of current iteration:

        AccumulateVector(resultLength,
                         integrandVector,
                         globalResult2);

        if(failed)
        {
            AccumulateVector(resultLength,
                             globalResult2,
                             integrandVector);

            break;
        }


        // Switch the buffers:

        double *t(NULL);

        t = globalResult1;

        globalResult1 = globalResult2;

        globalResult2 = t;

        t = subDomainBounds1;

        subDomainBounds1 = subDomainBounds2;

        subDomainBounds2 = t;
    }

    return 0;
}
