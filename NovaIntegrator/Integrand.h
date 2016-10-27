#ifndef INTEGRAND_H
#define INTEGRAND_H

#pragma once

#include "NovaDef.h"

namespace NovaIntegrator
{
  class Integrand
  {
  public:
     // Constructor:

     Integrand() {}

     // Destructor:

     virtual ~Integrand() {}

     // We overload the operator () of the
     // object for the integrand function call:

     virtual void operator ()
        (const double localCoord[],
         double* integrandVector,
         const unsigned vectorLength,
         const unsigned dataType = NovaDef::REAL_DATA_TYPE) = 0;
  };

  template <class T>
  class IntegrandTemplate : public Integrand
  {
  public:

     // A function pointer to a member function of class T

     typedef void (T::*IntegrandFunction)
                  (const double localCoord[],
                   double *integrandVector,
                   const unsigned vectorLength,
                   const unsigned dataType);

  protected:

     // Pointer to the calculator:

     T* m_calculator;

     // Pointer to the actual function:

     IntegrandFunction m_function;

  public:

     explicit IntegrandTemplate
              (T* calculator,
               IntegrandFunction nfunction) :

              Integrand(),
              m_calculator(calculator),
              m_function(nfunction)
        {}

     // Reset the integrand function:

     void ResetFunction(IntegrandFunction nfunction)
     {  m_function = nfunction; }

     // Returns true if passed function is equal to cached function:

     bool IsFunctionTheSame(IntegrandFunction nfunction) const
     { return nfunction == m_function; }

     // Reset the calculator pointer:

     void ResetCalculator( T* calculator )
     {  m_calculator = calculator; }

     // () operator:

     virtual void operator ()
         (const double localCoord[],
          double *integrandVector,
          const unsigned vectorLength,
          const unsigned dataType = NovaDef::REAL_DATA_TYPE )
     {
         (m_calculator->*m_function ) (localCoord,
                                       integrandVector,
                                       vectorLength,
                                       dataType);
     }
  };
}
#endif // INTEGRAND_H
