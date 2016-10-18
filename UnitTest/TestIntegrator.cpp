#include <iostream>
#include "GaussRule3D_Tet.h"
#include "TestIntegrator.h"

using namespace NovaIntegrator;

int TestIntegrator()
{
    GaussRule3D_Tet *rule_15 = GaussRule3D_Tet::GetInstance(15);

    unsigned dim = rule_15->GetDimension();

    const double *a(NULL), *w(NULL);

    unsigned num = rule_15->GetRule(a, w);

    for(unsigned i(0); i < num; ++i)
        std::cout << i << "  "
                  << a[i * dim] << "  "
                  << a[i * dim + 1] << "  "
                  << a[i * dim + 2] << "    "
                  << w[i]
                  << std::endl;

    return 0;

}
