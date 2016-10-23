#include <iostream>
#include "GaussRule1D.h"
#include "GaussRule2D_Tri.h"
#include "GaussRule3D_Tet.h"
#include "TestIntegrator.h"

using namespace NovaIntegrator;

int TestIntegrator()
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

    return 0;

}
