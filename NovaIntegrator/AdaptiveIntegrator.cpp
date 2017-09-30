#include "AdaptiveIntegrator.h"

const double NovaIntegrator::AdaptiveIntegrator::DEFAULT_ERR_TOL = 1e-3;

const double NovaIntegrator::AdaptiveIntegrator::DEFAULT_ABS_LIMIT = 1e-6;

const unsigned NovaIntegrator::AdaptiveIntegrator::MAX_NUM_SUBDOMAIN = 1024;

NovaIntegrator::AdaptiveIntegrator::
AdaptiveIntegrator():
    Integrator(),
    m_errTol(DEFAULT_ERR_TOL),
    m_absErrTol(DEFAULT_ABS_LIMIT),
    m_absErrorLimit(DEFAULT_ABS_LIMIT),
    m_errorEstimate(0.0),
    m_absoluteErr(false),
    m_errorType(MEAN_ERROR),
    m_numDomains(0),
    m_subdomainBoundsLength(0),
    m_subdomainBounds1(NULL),
    m_subdomainBounds2(NULL),
    m_fixedPntIntegrator(NULL),
    m_rule(NULL)
{}

void NovaIntegrator::AdaptiveIntegrator::
AllocateDomainBounds(const unsigned length)
{
    InitializeBoundSpace(length);
}

void NovaIntegrator::AdaptiveIntegrator::
AllocateSubdomainBounds(const unsigned length)
{
    if(length < m_subdomainBoundsLength)
        return;

    if(m_subdomainBounds1 != NULL)
    {
        delete[] m_subdomainBounds1;

        m_subdomainBounds1 = NULL;
    }

    m_subdomainBounds1 = new double[length * 2];

    m_subdomainBounds2 = m_subdomainBounds1 + length;

    m_subdomainBoundsLength = length;
}

void NovaIntegrator::AdaptiveIntegrator::
AccumulateVector(const unsigned length,
                 double *src,
                 double *dest)
{
    for(unsigned i(0); i < length; ++i)

        dest[i] += src[i];
}

void NovaIntegrator::AdaptiveIntegrator::
CopyVector(const unsigned length,
           double *src,
           double *dest)
{
    for(unsigned i(0); i < length; ++i)

        dest[i] = src[i];
}

double NovaIntegrator::AdaptiveIntegrator::
MagSquareOfArray(unsigned length,
                 double *data)
{
    double result(0.0);

    for(unsigned i(0); i < length; ++i)
    {
        double &element = data[i];

        result += element * element;
    }

    result /= double(length);

    return result;
}

double NovaIntegrator::AdaptiveIntegrator::
EstimateError(const unsigned length,
              const double *reference,
              const double *result1,
              const double *result2,
              bool &isAbsErr)
{
    isAbsErr = false;

    double error(0.0);

    double absReference(0.0);

    double temp(0.0);

    switch(m_errorType)
    {
    case MEAN_ERROR:

        for(unsigned i(0); i < length; ++i)
        {
            temp = std::fabs(result2[i] - result1[i]);

            absReference = std::fabs(reference[i]);

            if(absReference > m_absErrorLimit)

                error += temp / absReference;

            else
            {
                error += temp;

                isAbsErr = true;
            }
        }

        error /= double(length);

        break;

    case MAX_ERROR:

        for(unsigned i(0); i < length; ++i)
        {
            temp = std::fabs(result2[i] - result1[i]);

            absReference = std::fabs(reference[i]);

            if(absReference > m_absErrorLimit)

                temp /= absReference;

            else

                isAbsErr = true;

            if(temp > error)

                error = temp;

        }

        break;

    case NORMP2_ERROR:

        for(unsigned i(0); i < length; ++i)
        {
            temp = result2[i] - result1[i];

            error += temp * temp;

            temp = reference[i];

            absReference += temp * temp;
        }

        if(absReference > m_absErrorLimit)

            error = std::sqrt(error / absReference);

        else
        {
            error = std::sqrt(error);

            isAbsErr = true;
        }

        break;

    default:

        break;
    }

    return error;
}

unsigned NovaIntegrator::AdaptiveIntegrator::
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

    unsigned numResultVec = 4;

    InitializeWorkspace(resultLength * numResultVec);

    double *globalResult1 = m_workspace;

    double *globalResult2 = globalResult1 + resultLength;

    double *resultLow = globalResult2 + resultLength;

    double *resultHigh = resultLow + resultLength;

    // Set the fixed point integration rules:

    IntegrationRule *ruleLow = m_rule[0];

    IntegrationRule *ruleHigh = m_rule[1];

    // Estimate the integral over the entire domain:

    m_fixedPntIntegrator->SetRule(ruleLow);

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

    double error(0.0);

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

            m_fixedPntIntegrator->SetRule(ruleLow);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultLow,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Compute integral using higher order rule:

            m_fixedPntIntegrator->SetRule(ruleHigh);

            m_fixedPntIntegrator->Integrate(integrand,
                                            resultHigh,
                                            vectorLength,
                                            dataType);

            m_numFuncEval += m_fixedPntIntegrator->GetNumFuncEval();

            // Estimate error:

            error = EstimateError(resultLength,
                                  globalResult1,
                                  resultLow,
                                  resultHigh,
                                  isAbsErr);

            // Check convergence:

            if(isAbsErr)
            {
                m_absoluteErr = true;

                converged = error < absErrTol;
            }

            else

                converged = error < errTol;

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
                    SplitDomain(currentSubDomain, newSubDomain);

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
