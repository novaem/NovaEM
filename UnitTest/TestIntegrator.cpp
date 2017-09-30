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

    integrandVector[0] = L1 * L1 * L1 * L1 * L1 * L1 * L1 * L1 * L1 * L1+
                         2.0 * L1 * L1 * L1 * L1 * L1;

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

    integrandVector[0] = L1 * L1 * L1 * L1 * L1 * L1 * L2 * L2 +
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

    integrandVector[0] = L1 * L1 * L1 * L1 * L2 * L2 * L2 * L3 * L3 * L3 +
                         2.0 * L1 * L1 * L1 * L2 * L2 * L2 * L2 * L3 * L3 * L3 +
                         3.0 * L1 * L1 * L1 * L2 * L2 * L2 * L3 * L3 * L3 * L3;

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

    integrator1d.SetOrder(10);

    integrator1d.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (x^10 + 2*x^5) over (0.5, 0) is: "
              << result[0]
              << " (with "
              << integrator1d.GetNumFuncEval()
              << " function evaluations.)"
              << std::endl;

    NovaIntegrator::AdaptiveIntegrator1D adaptive1d;

    adaptive1d.SetBounds(2, bounds);

    adaptive1d.SetOrder(5);

    adaptive1d.SetErrTol(1e-4);

    adaptive1d.Integrate(m_integrandObj,
                         result,
                         1,
                         NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (x^10 + 2*x^5) over (0.5, 0) is: "
              << result[0]
              << " (with "
              << adaptive1d.GetNumFuncEval()
              << " function evaluations.)"
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

    integratorTri.SetOrder(8);

    integratorTri.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^6 * v^2 + 2 * u * v^2) over a triangle is: "
              << result[0]
              << " (with "
              << integratorTri.GetNumFuncEval()
              << " function evaluations.)"
              << std::endl;

    NovaIntegrator::AdaptiveIntegrator2D_Tri adaptive2d_tri;

    adaptive2d_tri.SetBounds(6, bounds);

    adaptive2d_tri.SetOrder(3);

    adaptive2d_tri.Integrate(m_integrandObj,
                             result,
                             1,
                             NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^6 * v^2 + 2 * u * v^2) over a triangle is: "
              << result[0]
              << " (with "
              << adaptive2d_tri.GetNumFuncEval()
              << " function evaluations.)"
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

    integratorQuad.SetOrder(8);

    integratorQuad.Integrate(m_integrandObj,
                             result,
                             1,
                             NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^6 * v^2 + 2 * u * v^2) over a triangle is: "
              << result[0]
              << " (with "
              << integratorQuad.GetNumFuncEval()
              << " function evaluations.)"
              << std::endl;

    NovaIntegrator::AdaptiveIntegrator2D_Quad adaptive2d_quad;

    adaptive2d_quad.SetBounds(8, bounds);

    adaptive2d_quad.SetOrder(3);

    adaptive2d_quad.Integrate(m_integrandObj,
                              result,
                              1,
                              NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^6 * v^2 + 2 * u * v^2) over a triangle is: "
              << result[0]
              << " (with "
              << adaptive2d_quad.GetNumFuncEval()
              << " function evaluations.)"
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

    integratorTet.SetOrder(12);

    integratorTet.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^4 * v^3 * w^3 + 2 * u^3 * v^4 * w^3 + 3 * u^3 * v^3 * w^4) over a tet is: "
              << result[0]
              << " (with "
              << integratorTet.GetNumFuncEval()
              << " function evaluations.)"
              << std::endl;

    NovaIntegrator::AdaptiveIntegrator3D_Tet adaptive3d_tet;

    adaptive3d_tet.SetBounds(12, bounds);

    adaptive3d_tet.SetOrder(3);

    adaptive3d_tet.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^4 * v^3 * w^3 + 2 * u^3 * v^4 * w^3 + 3 * u^3 * v^3 * w^4) over a tet is: "
              << result[0]
              << " (with "
              << adaptive3d_tet.GetNumFuncEval()
              << " function evaluations.)"
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
    bounds[11] = 0.0;

    bounds[12] = 0.0;
    bounds[13] = 0.0;
    bounds[14] = 0.0;

    bounds[15] = 0.0;
    bounds[16] = 0.0;
    bounds[17] = 1.3;

    bounds[18] = 0.0;
    bounds[19] = 0.0;
    bounds[20] = 1.3;

    bounds[21] = 0.0;
    bounds[22] = 0.0;
    bounds[23] = 0.0;


    m_integrandObj->ResetFunction(&IntTester::IntegrandTet);

    NovaIntegrator::FixedPntIntegrator3D_Hex integratorHex;

    integratorHex.SetBounds(24, bounds);

    integratorHex.SetOrder(12);

    integratorHex.Integrate(m_integrandObj,
                           result,
                           1,
                           NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^4 * v^3 * w^3 + 2 * u^3 * v^4 * w^3 + 3 * u^3 * v^3 * w^4) over a tet is: "
              << result[0]
              << " (with "
              << integratorHex.GetNumFuncEval()
              << " function evaluations.)"
              << std::endl;

    NovaIntegrator::AdaptiveIntegrator3D_Hex adaptive3d_hex;

    adaptive3d_hex.SetBounds(24, bounds);

    adaptive3d_hex.SetOrder(3);

    adaptive3d_hex.Integrate(m_integrandObj,
                             result,
                             1,
                             NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (u^4 * v^3 * w^3 + 2 * u^3 * v^4 * w^3 + 3 * u^3 * v^3 * w^4) over a tet is: "
              << result[0]
              << " (with "
              << adaptive3d_hex.GetNumFuncEval()
              << " function evaluations.)"
              << std::endl;

    return 0;

}
