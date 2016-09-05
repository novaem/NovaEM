#include <iostream>
#include "R3.h"
#include "TestR3.h"

using namespace NovaType;

int TestR3()
{
    std::cout << "Testing vector calculation ..." << std::endl;

    R3 r1(1, 2, 3);

    R3 r2(4, 5, 6);

    R3 r(r1.GetCoord());

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1;

    r = r1 * 2.0;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r / 2.0;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = 2.0 * r1;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1 + r2;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1 - r2;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    std::cout << r1.Mag() << std::endl;

    std::cout << r1.Dot(r2) << std::endl;

    r = r1.Cross(r2);

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1;

    r.Negate();

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1;

    r.Normalize();

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    r = r1;

    double *coord = r.GetCoord();

    coord[0] = 7;

    r.GetCoord(1) = 8;

    std::cout << r[0] << "    "
              << r[1] << "    "
              << r[2] << std::endl;

    const R3 rConst(1, 2, 3);

    std::cout << rConst[0] << "    "
              << rConst[1] << "    "
              << rConst[2] << std::endl;

    const double *constCoord = rConst.GetCoord();

    for(unsigned i(0); i < 3; ++i)
    {
        std::cout << constCoord[i] << "    ";
    }

    std::cout << std::endl;


    for(unsigned i(0); i < 3; ++i)
    {
        std::cout << rConst.GetCoord(i) << "    ";
    }

    std::cout << std::endl;

    std::cout << "Vector calculation test is done."
              << std::endl << std::endl;

    return 0;

}
