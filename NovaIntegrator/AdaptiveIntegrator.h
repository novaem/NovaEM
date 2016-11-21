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

    protected:

        double m_errTol;

        double m_absErrorLimit;

        double m_errorEstimate;

        bool m_absoluteErr;

        ErrorType m_errorType;

        unsigned m_numDomains;

        unsigned m_domainBoundsLength;

        // Length of subdomain bounds array:

        unsigned m_subdomainBoundsLength;

        double *m_subdomainBounds1;

        double *m_subdomainBounds2;

        FixedPointIntegrator *m_fixedPntIntegrator;

        IntegrationRule **m_rule;

        virtual double ComputeJacobian(const double lc[]) = 0;

        virtual void ComputeLocalCoordinate(const double lc[],
                                            double localCoord[]) = 0;

        void CleanUp()
        {
            if(m_rule != NULL)
            {
                delete[] m_rule;

                m_rule = NULL;
            }
        }

        void InitializeRule(const unsigned numRule)
        {
            CleanUp();

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

        // Set number of domains:

        virtual void SetNumDomain(const unsigned numDomains) = 0;
    };
}


#endif // ADAPTIVEINTEGRATOR_H
