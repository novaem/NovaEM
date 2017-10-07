#ifndef ADAPTIVEINTEGRATOR_H
#define ADAPTIVEINTEGRATOR_H


#pragma once

#include "Integrator.h"
#include "FixedPointIntegrator.h"

namespace NovaIntegrator
{

    class AdaptiveIntegrator : public Integrator
    {
    public:

        enum ErrorType{MEAN_ERROR, MAX_ERROR, NORMP2_ERROR};

        const static double DEFAULT_ERR_TOL;

        const static double DEFAULT_ABS_LIMIT;

        const static unsigned MAX_NUM_SUBDOMAIN;

    protected:

        // Error tolerance:

        double m_errTol;

        double m_absErrTol;

        // The lower limit of the magnitude of the integrand.
        // When the integrand is smaller than this limit,
        // absolute error, instead of relative error, will
        // be used to check convergence:

        double m_absErrorLimit;

        // The estimated error of current iteration:

        double m_errorEstimate;

        // Flag tells if absolute error is used:

        bool m_absoluteErr;

        // The way in which the error is computed:

        ErrorType m_errorType;

        // The initial number of domains to be integrated:

        unsigned m_numDomains;

        // Length of subdomain bounds array:

        unsigned m_subdomainBoundsLength;

        double *m_subdomainBounds1;

        double *m_subdomainBounds2;

        FixedPointIntegrator *m_fixedPntIntegrator;

        IntegrationRule **m_rule;

        void CleanUp()
        {
            m_subdomainBoundsLength = 0;

            if(m_subdomainBounds1 != NULL)
            {
                delete[] m_subdomainBounds1;

                m_subdomainBounds1 = NULL;
            }

            if(m_fixedPntIntegrator != NULL)

                delete m_fixedPntIntegrator;

            if(m_rule != NULL)
            {
                delete[] m_rule;

                m_rule = NULL;
            }
        }

        void InitializeRule(const unsigned numRule)
        {
            if(m_rule != NULL)
            {
                delete[] m_rule;

                m_rule = NULL;
            }

            m_rule = new IntegrationRule *[numRule];
        }

        void AllocateDomainBounds(const unsigned length);

        void AllocateSubdomainBounds(const unsigned length);

        void AccumulateVector(const unsigned length,
                              double *src,
                              double *dest);

        void CopyVector(const unsigned length,
                        double *src,
                        double *dest);

        double MagSquareOfArray(unsigned length,
                                double *data);

        // Estimate the errors:

        double EstimateError(const unsigned length,
                             const double *reference,
                             const double *result1,
                             const double *result2,
                             bool &isAbsErr);

        virtual unsigned GetBoundRecLength() const = 0;

        virtual unsigned GetSplitDomainNum() const = 0;

        virtual void SplitDomain(double *oldDomain,
                                 double *newDomain,
                                 unsigned splitDirection = 0) = 0;

    public:

        // Default constructor:

        AdaptiveIntegrator();

        // Destructor:

        virtual ~AdaptiveIntegrator()
        {
            CleanUp();
        }

        // Set the error tolerance for adaptive integrator:

        void SetErrTol(const double &errTol)
        {
            m_errTol = errTol;
        }

        virtual bool IsSingularIntegrator() const
        {
            return false;
        }

        virtual bool IsAdaptiveIntegrator() const
        {
            return true;
        }

        virtual unsigned Integrate(Integrand *integrand,
                                   double *integrandVector,
                                   const unsigned vectorLength,
                                   const unsigned dataType);

        // Set number of domains:

        virtual void SetNumDomain(const unsigned numDomains) = 0;

    };
}


#endif // ADAPTIVEINTEGRATOR_H
