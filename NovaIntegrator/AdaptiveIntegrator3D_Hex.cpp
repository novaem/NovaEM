#include "GaussRule1D.h"
#include "FixedPntIntegrator3D_Hex.h"
#include "AdaptiveIntegrator3D_Hex.h"
using namespace NovaIntegrator;

const unsigned
AdaptiveIntegrator3D_Hex::NUM_VERTEX = 8;

const unsigned
AdaptiveIntegrator3D_Hex::DIM = NovaDef::DIM_3D;

const unsigned
AdaptiveIntegrator3D_Hex::BOUND_REC_LENGTH =
        AdaptiveIntegrator3D_Hex::NUM_VERTEX *
        AdaptiveIntegrator3D_Hex::DIM;

AdaptiveIntegrator3D_Hex::
AdaptiveIntegrator3D_Hex(const unsigned order) : AdaptiveIntegrator()
{
    InitializeRule(2);

    m_rule[0] = GaussRule1D::GetInstance(order);

    m_rule[1] = GaussRule1D::GetNextOrderInstance(order);

    m_fixedPntIntegrator = new FixedPntIntegrator3D_Hex;

    m_numDomains = 1;

    unsigned length = BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

AdaptiveIntegrator3D_Hex::~AdaptiveIntegrator3D_Hex()
{
}

void AdaptiveIntegrator3D_Hex::SetNumDomain(unsigned numDomain)
{
    m_numDomains = numDomain;

    unsigned length = numDomain * BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

void AdaptiveIntegrator3D_Hex::SetOrder(const unsigned order)
{
    m_rule[0] = GaussRule1D::GetInstance(order);

    m_rule[1] = GaussRule1D::GetNextOrderInstance(order);
}

unsigned AdaptiveIntegrator3D_Hex::GetBoundRecLength() const
{
    return BOUND_REC_LENGTH;
}

unsigned AdaptiveIntegrator3D_Hex::GetSplitDomainNum() const
{
    return 2;
}

void AdaptiveIntegrator3D_Hex::
SplitDomain(double *oldDomain,
            double *newDomain,
            unsigned splitDirection)
{
    double &x0 = oldDomain[0];
    double &y0 = oldDomain[1];
    double &z0 = oldDomain[2];

    double &x1 = oldDomain[3];
    double &y1 = oldDomain[4];
    double &z1 = oldDomain[5];

    double &x2 = oldDomain[6];
    double &y2 = oldDomain[7];
    double &z2 = oldDomain[8];

    double &x3 = oldDomain[9];
    double &y3 = oldDomain[10];
    double &z3 = oldDomain[11];

    double &x4 = oldDomain[12];
    double &y4 = oldDomain[13];
    double &z4 = oldDomain[14];

    double &x5 = oldDomain[15];
    double &y5 = oldDomain[16];
    double &z5 = oldDomain[17];

    double &x6 = oldDomain[18];
    double &y6 = oldDomain[19];
    double &z6 = oldDomain[20];

    double &x7 = oldDomain[21];
    double &y7 = oldDomain[22];
    double &z7 = oldDomain[23];

    double *subDomain = newDomain;

    double nx0, nx1, nx2, nx3;

    double ny0, ny1, ny2, ny3;

    double nz0, nz1, nz2, nz3;

    switch(splitDirection)
    {

    case 0:

        nx0 = (x0 + x1) / 2.0;
        ny0 = (y0 + y1) / 2.0;
        nz0 = (z0 + z1) / 2.0;


        nx1 = (x3 + x2) / 2.0;
        ny1 = (y3 + y2) / 2.0;
        nz1 = (z3 + z2) / 2.0;

        nx2 = (x4 + x5) / 2.0;
        ny2 = (y4 + y5) / 2.0;
        nz2 = (z4 + z5) / 2.0;

        nx3 = (x7 + x6) / 2.0;
        ny3 = (y7 + y6) / 2.0;
        nz3 = (z7 + z6) / 2.0;

        // Sub domain 0:

        subDomain[0] = x0;
        subDomain[1] = y0;
        subDomain[2] = z0;

        subDomain[3] = nx0;
        subDomain[4] = ny0;
        subDomain[5] = nz0;

        subDomain[6] = nx1;
        subDomain[7] = ny1;
        subDomain[8] = nz1;

        subDomain[9] = x3;
        subDomain[10] = y3;
        subDomain[11] = z3;

        subDomain[12] = x4;
        subDomain[13] = y4;
        subDomain[14] = z4;

        subDomain[15] = nx2;
        subDomain[16] = ny2;
        subDomain[17] = nz2;

        subDomain[18] = nx3;
        subDomain[19] = ny3;
        subDomain[20] = nz3;

        subDomain[21] = x7;
        subDomain[22] = y7;
        subDomain[23] = z7;

        subDomain += BOUND_REC_LENGTH;

        // Sub domain 1:

        subDomain[0] = nx0;
        subDomain[1] = ny0;
        subDomain[2] = nz0;

        subDomain[3] = x1;
        subDomain[4] = y1;
        subDomain[5] = z1;

        subDomain[6] = x2;
        subDomain[7] = y2;
        subDomain[8] = z2;

        subDomain[9] = nx1;
        subDomain[10] = ny1;
        subDomain[11] = nz1;

        subDomain[12] = nx2;
        subDomain[13] = ny2;
        subDomain[14] = nz2;

        subDomain[15] = x5;
        subDomain[16] = y5;
        subDomain[17] = z5;

        subDomain[18] = x6;
        subDomain[19] = y6;
        subDomain[20] = z6;

        subDomain[21] = nx3;
        subDomain[22] = ny3;
        subDomain[23] = nz3;

        break;

    case 1:

        nx0 = (x0 + x3) / 2.0;
        ny0 = (y0 + y3) / 2.0;
        nz0 = (z0 + z3) / 2.0;


        nx1 = (x1 + x2) / 2.0;
        ny1 = (y1 + y2) / 2.0;
        nz1 = (z1 + z2) / 2.0;

        nx2 = (x4 + x7) / 2.0;
        ny2 = (y4 + y7) / 2.0;
        nz2 = (z4 + z7) / 2.0;

        nx3 = (x5 + x6) / 2.0;
        ny3 = (y5 + y6) / 2.0;
        nz3 = (z5 + z6) / 2.0;

        // Sub domain 0:

        subDomain[0] = x0;
        subDomain[1] = y0;
        subDomain[2] = z0;

        subDomain[3] = x1;
        subDomain[4] = y1;
        subDomain[5] = z1;

        subDomain[6] = nx1;
        subDomain[7] = ny1;
        subDomain[8] = nz1;

        subDomain[9] = nx0;
        subDomain[10] = ny0;
        subDomain[11] = nz0;

        subDomain[12] = x4;
        subDomain[13] = y4;
        subDomain[14] = z4;

        subDomain[15] = x5;
        subDomain[16] = y5;
        subDomain[17] = z5;

        subDomain[18] = nx3;
        subDomain[19] = ny3;
        subDomain[20] = nz3;

        subDomain[21] = nx2;
        subDomain[22] = ny2;
        subDomain[23] = nz2;

        subDomain += BOUND_REC_LENGTH;

        // Sub domain 1:

        subDomain[0] = nx0;
        subDomain[1] = ny0;
        subDomain[2] = nz0;

        subDomain[3] = nx1;
        subDomain[4] = ny1;
        subDomain[5] = nz1;

        subDomain[6] = x2;
        subDomain[7] = y2;
        subDomain[8] = z2;

        subDomain[9] = x3;
        subDomain[10] = y3;
        subDomain[11] = z3;

        subDomain[12] = nx2;
        subDomain[13] = ny2;
        subDomain[14] = nz2;

        subDomain[15] = nx3;
        subDomain[16] = ny3;
        subDomain[17] = nz3;

        subDomain[18] = x6;
        subDomain[19] = y6;
        subDomain[20] = z6;

        subDomain[21] = x7;
        subDomain[22] = y7;
        subDomain[23] = z7;

        break;


    case 2:

        nx0 = (x0 + x4) / 2.0;
        ny0 = (y0 + y4) / 2.0;
        nz0 = (z0 + z4) / 2.0;


        nx1 = (x1 + x5) / 2.0;
        ny1 = (y1 + y5) / 2.0;
        nz1 = (z1 + z5) / 2.0;

        nx2 = (x3 + x7) / 2.0;
        ny2 = (y3 + y7) / 2.0;
        nz2 = (z3 + z7) / 2.0;

        nx3 = (x2 + x6) / 2.0;
        ny3 = (y2 + y6) / 2.0;
        nz3 = (z2 + z6) / 2.0;

        // Sub domain 0:

        subDomain[0] = x0;
        subDomain[1] = y0;
        subDomain[2] = z0;

        subDomain[3] = x1;
        subDomain[4] = y1;
        subDomain[5] = z1;

        subDomain[6] = x2;
        subDomain[7] = y2;
        subDomain[8] = z2;

        subDomain[9] = x3;
        subDomain[10] = y3;
        subDomain[11] = z3;

        subDomain[12] = nx0;
        subDomain[13] = ny0;
        subDomain[14] = nz0;

        subDomain[15] = nx1;
        subDomain[16] = ny1;
        subDomain[17] = nz1;

        subDomain[18] = nx3;
        subDomain[19] = ny3;
        subDomain[20] = nz3;

        subDomain[21] = nx2;
        subDomain[22] = ny2;
        subDomain[23] = nz2;

        subDomain += BOUND_REC_LENGTH;

        // Sub domain 1:

        subDomain[0] = nx0;
        subDomain[1] = ny0;
        subDomain[2] = nz0;

        subDomain[3] = nx1;
        subDomain[4] = ny1;
        subDomain[5] = nz1;

        subDomain[6] = nx3;
        subDomain[7] = ny3;
        subDomain[8] = nz3;

        subDomain[9] = nx2;
        subDomain[10] = ny2;
        subDomain[11] = nz2;

        subDomain[12] = x4;
        subDomain[13] = y4;
        subDomain[14] = z4;

        subDomain[15] = x5;
        subDomain[16] = y5;
        subDomain[17] = z5;

        subDomain[18] = x6;
        subDomain[19] = y6;
        subDomain[20] = z6;

        subDomain[21] = x7;
        subDomain[22] = y7;
        subDomain[23] = z7;

        break;

    default:

        break;
    }
}

unsigned NovaIntegrator::AdaptiveIntegrator3D_Hex::
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

    unsigned numResultVec = 6;

    InitializeWorkspace(resultLength * numResultVec);

    double *globalResult1 = m_workspace;

    double *globalResult2 = globalResult1 + resultLength;

    double *resultLow = globalResult2 + resultLength;

    double *resultHigh0 = resultLow + resultLength;

    double *resultHigh1 = resultHigh0 + resultLength;

    double *resultHigh2 = resultHigh1 + resultLength;

    double *resultHigh(NULL);

    // Set the fixed point integration rules:

    IntegrationRule *ruleLow = m_rule[0];

    IntegrationRule *ruleHigh = m_rule[1];

    // Estimate the integral over the entire domain:

    m_fixedPntIntegrator->SetRule(ruleLow, 0);

    m_fixedPntIntegrator->SetRule(ruleLow, 1);

    m_fixedPntIntegrator->SetRule(ruleLow, 2);

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

    double error(0.0), error0(0.0), error1(0.0), error2(0.0);

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

            m_fixedPntIntegrator->SetRule(ruleLow, 2);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultLow,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Compute integral using higher order rule along x direction:

            m_fixedPntIntegrator->SetRule(ruleHigh, 0);

            m_fixedPntIntegrator->SetRule(ruleLow, 1);

            m_fixedPntIntegrator->SetRule(ruleLow, 2);

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

            m_fixedPntIntegrator->SetRule(ruleLow, 2);

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

            // Compute integral using higher order rule along y direction:

            m_fixedPntIntegrator->SetRule(ruleLow, 0);

            m_fixedPntIntegrator->SetRule(ruleLow, 1);

            m_fixedPntIntegrator->SetRule(ruleHigh, 2);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultHigh2,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Estimate error:

            error2 = EstimateError(resultLength,
                                   globalResult1,
                                   resultLow,
                                   resultHigh2,
                                   isAbsErr);

            // Check convergence:

            if(isAbsErr)
            {
                m_absoluteErr = true;

                converged = converged && error2 < absErrTol;
            }

            else

                converged = converged && error2 < errTol;

            if(error0 < error1)
            {
                resultHigh = resultHigh0;

                error = error1;

                splitDir = 1;
            }

            else
            {
                resultHigh = resultHigh1;

                error = error0;

                splitDir = 0;
            }

            if(error < error2)
            {
                resultHigh = resultHigh2;

                error = error2;

                splitDir = 2;
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
