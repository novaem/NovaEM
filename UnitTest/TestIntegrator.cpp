#include <iostream>
#include "GaussRule1D.h"
#include "GaussRule2D_Tri.h"
#include "GaussRule3D_Tet.h"
#include "TestIntegrator.h"

using namespace NovaIntegrator;

IntTester::IntTester():
    m_integrandObj(NULL)
{
    m_integrandObj = new TestIntegrand(this, NULL);
}

IntTester::~IntTester()
{
    if(m_integrandObj != NULL)
    {
        delete m_integrandObj;

        m_integrandObj = NULL;
    }
}

void IntTester::
Integrand1D(const double localCoord[],
            double *integrandVector,
            const unsigned vectorLength,
            const unsigned dataType)
{
    const double &L1 = localCoord[0];

    integrandVector[0] = L1 * L1 * L1 * L1 * L1 +
                         2.0 * L1 * L1 * L1;

    return;
}

void IntTester::
IntegrandTri(const double localCoord[],
             double *integrandVector,
             const unsigned vectorLength,
             const unsigned dataType)
{
    const double &L1 = localCoord[0];

    const double &L2 = localCoord[1];

    integrandVector[0] = L1 * L1 * L1 * L2 * L2 +
                         2.0 * L2 * L2 * L1;

    return;
}

void IntTester::
IntegrandTet(const double localCoord[],
             double *integrandVector,
             const unsigned vectorLength,
             const unsigned dataType)
{
    const double &L1 = localCoord[0];

    const double &L2 = localCoord[1];

    const double &L3 = localCoord[2];

    integrandVector[0] = L1 * L1 * L2 * L3 +
                         2.0 * L1 * L2 * L2 * L3 +
                         3.0 * L1 * L2 * L3 * L3 ;

    return;
}

int IntTester::TestRule()
{
    IntegrationRule *rule(NULL);

    rule = GaussRule3D_Tet::GetInstance(15);

    unsigned dim = rule->GetDimension();

    const double *a(NULL), *w(NULL);

    unsigned num = rule->GetRule(a, w);

    for(unsigned i(0); i < num; ++i)
        std::cout << i << "  "
                  << a[i * dim] << "  "
                  << a[i * dim + 1] << "  "
                  << a[i * dim + 2] << "    "
                  << w[i]
                  << std::endl;

    std::cout<< std::endl;

    rule = GaussRule2D_Tri::GetInstance(15);

    dim = rule->GetDimension();

    num = rule->GetRule(a, w);

    for(unsigned i(0); i < num; ++i)
        std::cout << i << "  "
                  << a[i * dim] << "  "
                  << a[i * dim + 1] << "  "
                  << w[i]
                  << std::endl;

    std::cout<< std::endl;

    rule = GaussRule1D::GetInstance(15);

    dim = rule->GetDimension();

    num = rule->GetRule(a, w);

    for(unsigned i(0); i < num; ++i)
        std::cout << i << "  "
                  << a[i * dim] << "  "
                  << w[i]
                  << std::endl;

    std::cout << std::endl;

    return 0;

}

int IntTester::TestIntegrator()
{
    double result[128];

    double bounds[128];

    bounds[0] = 0.5;

    bounds[1] = 0.0;

    m_integrandObj->ResetFunction(&IntTester::Integrand1D);

    NovaIntegrator::FixedPntIntegrator1D integrator1d;

    integrator1d.SetBounds(2, bounds);

    integrator1d.SetOrder(5);

    integrator1d.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (x^5 + 2*x^3) over (0.5, 0) is: "
              << result[0]
              << std::endl;

    bounds[0] = 0.0;
    bounds[1] = 0.0;

    bounds[2] = 0.5;
    bounds[3] = 0.0;

    bounds[4] = 0.0;
    bounds[5] = 0.7;

    m_integrandObj->ResetFunction(&IntTester::IntegrandTri);

    NovaIntegrator::FixedPntIntegrator2D_Tri integratorTri;

    integratorTri.SetBounds(6, bounds);

    integratorTri.SetOrder(5);

    integratorTri.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^3 * v^2 + 2 * u * v^2) over a triangle is: "
              << result[0]
              << std::endl;

    bounds[0] = 0.0;
    bounds[1] = 0.0;

    bounds[2] = 0.5;
    bounds[3] = 0.0;

    bounds[4] = 0.0;
    bounds[5] = 0.7;

    bounds[6] = 0.0;
    bounds[7] = 0.0;

    m_integrandObj->ResetFunction(&IntTester::IntegrandTri);

    NovaIntegrator::FixedPntIntegrator2D_Quad integratorQuad;

    integratorQuad.SetBounds(8, bounds);

    integratorQuad.SetOrder(6);

    integratorQuad.Integrate(m_integrandObj,
                             result,
                             1,
                             NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^3 * v^2 + 2 * u * v^2) over a triangle is: "
              << result[0]
              << std::endl;

    bounds[0] = 0.0;
    bounds[1] = 0.0;
    bounds[2] = 0.;

    bounds[3] = 1.1;
    bounds[4] = 0.0;
    bounds[5] = 0.0;

    bounds[6] = 0.0;
    bounds[7] = 1.2;
    bounds[8] = 0.0;

    bounds[9] = 0.0;
    bounds[10] = 0.0;
    bounds[11] = 1.3;


    m_integrandObj->ResetFunction(&IntTester::IntegrandTet);

    NovaIntegrator::FixedPntIntegrator3D_Tet integratorTet;

    integratorTet.SetBounds(12, bounds);

    integratorTet.SetOrder(4);

    integratorTet.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^2 * v * w + 2 * u * v^2 * w + 3 * u * v * w^2) over a tet is: "
              << result[0]
              << std::endl;

    return 0;

}
