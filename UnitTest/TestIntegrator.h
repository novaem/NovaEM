#ifndef TESTINTEGRATOR_H
#define TESTINTEGRATOR_H

#pragma once

#include "FixedPntIntegrator1D.h"
#include "FixedPntIntegrator2D_Tri.h"
#include "FixedPntIntegrator2D_Quad.h"
#include "FixedPntIntegrator3D_Tet.h"
#include "FixedPntIntegrator3D_Hex.h"
#include "AdaptiveIntegrator1D.h"
#include "AdaptiveIntegrator2D_Tri.h"
#include "AdaptiveIntegrator2D_Quad.h"
#include "AdaptiveIntegrator3D_Tet.h"
#include "AdaptiveIntegrator3D_Hex.h"
#include "DuffyIntegrator2D_Tri.h"
#include "DuffyIntegrator2D_Quad.h"

class IntTester
{
private:

    typedef NovaIntegrator::IntegrandTemplate<IntTester> TestIntegrand;

protected:

    TestIntegrand *m_integrandObj;

public:

    IntTester();

    virtual ~IntTester();

    void Integrand1D(const double localCoord[],
                     double *integrandVector,
                     const unsigned vectorLength,
                     const unsigned dataType);

    void IntegrandTri(const double localCoord[],
                      double *integrandVector,
                      const unsigned vectorLength,
                      const unsigned dataType);

    void IntegrandTet(const double localCoord[],
                      double *integrandVector,
                      const unsigned vectorLength,
                      const unsigned dataType);

    void SingularIntegrand2D(const double localCoord[],
                             double *integrandVector,
                             const unsigned vectorLength,
                             const unsigned dataType);

    int TestRule();

    int TestIntegrator();

};

#endif // TESTINTEGRATOR_H
