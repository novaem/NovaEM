#include "AdaptiveIntegrator.h"

const double NovaIntegrator::AdaptiveIntegrator::DEFAULT_ERR_TOL = 1e-3;

const double NovaIntegrator::AdaptiveIntegrator::DEFAULT_ABS_LIMIT = 1e-6;

NovaIntegrator::AdaptiveIntegrator::
AdaptiveIntegrator():
    Integrator(),
    m_errTol(DEFAULT_ERR_TOL),
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
    InitializeBounds(length);
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

    if(m_subdomainBounds2 != NULL)
    {
        delete[] m_subdomainBounds2;

        m_subdomainBounds2 = NULL;
    }

    m_subdomainBounds1 = new double[length];

    m_subdomainBounds2 = new double[length];

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

                error += temp;
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

            error = std::sqrt(error);

        break;

    default:

        break;
    }

    return error;
}
