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
    m_integrandObj->ResetFunction(&IntTester::Integrand1D);

    NovaIntegrator::FixedPntIntegrator1D integrator;

    double result[128];

    integrator.SetOrder(5);

    integrator.Integrate(m_integrandObj,
                         result,
                         1,
                         NovaDef::REAL_DATA_TYPE);

    std::cout.precision(15);

    std::cout << "The integral of (x^5 + 2*x^3) over (0, 1) is: "
              << result[0]
              << std::endl;

    return 0;

}
