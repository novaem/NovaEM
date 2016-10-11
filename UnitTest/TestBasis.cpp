#include <iostream>
#include "DivBasisTri.h"
#include "DivBasisQuad.h"
#include "DivBasisTet.h"
#include "DivBasisHex.h"
#include "Triangle.h"
#include "Tet.h"
#include "Quad.h"
#include "Hex.h"
#include "TestR3.h"

using namespace NovaMesh;
using namespace NovaBasis;


int TestBasis()
{
    NovaType::R3 v[8];

    const NovaType::R3 *av[8];

    av[0] = &v[0];

    av[1] = &v[1];

    av[2] = &v[2];

    av[3] = &v[3];

    av[4] = &v[4];

    av[5] = &v[5];

    av[6] = &v[6];

    av[7] = &v[7];

    v[0].Set(0.0, 0.0, 0.0);
    v[1].Set(1.0, 0.0, 0.0);
    v[2].Set(0.0, 1.0, 0.0);
    v[3].Set(0.0, 0.0, 1.0);

    double lc[] = {1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0};

    NovaType::R3 t, r;

    NovaType::R3 unit[3];

    double bnValue[3];

    std::cout << "Testing basis function on triangle ..."
              << std::endl << std::endl;

    NovaBasis::DivBasisTri triBasis;

    NovaMesh::Triangle triangle;

    triangle.Initialize(0, (const NovaType::R3 **) (av));

    triangle.ComputeGlobalCoord(lc, r);

    triangle.ComputeUnitaryVectors(lc, unit);

    for(unsigned i(0); i < triangle.GetNumNodes(); ++i)
    {
        t.Set(r);

        t.Subtract(v[i]);

        std::cout << "Reference "
                  << i << ":    "
                  << t[0] << "    "
                  << t[1] << "    "
                  << t[2]
                  << std::endl << std::endl;

        triBasis.ComputeBn(i, lc, bnValue);

        t.Set(bnValue[0], unit[0]);

        t.Add(bnValue[1], unit[1]);

        std::cout << "Basis Fn "
                  << i << ":    "
                  << t[0] << "    "
                  << t[1] << "    "
                  << t[2]
                  << std::endl << std::endl;

        triBasis.ComputeDiv(i, lc, bnValue);

        std::cout << "Divergence "
                  << i << ":    "
                  << bnValue[0]
                  << std::endl << std::endl;

    }

    std::cout << "Test of basis function on triangle is done!"
              << std::endl << std::endl;

    std::cout << "Testing basis function on tet ..."
              << std::endl << std::endl;

    NovaBasis::DivBasisTet tetBasis;

    NovaMesh::Tet tet;

    tet.Initialize(2, (const NovaType::R3 **) (av));

    tet.ComputeGlobalCoord(lc, r);

    tet.ComputeUnitaryVectors(lc, unit);

    for(unsigned i(0); i < tet.GetNumNodes(); ++i)
    {
        t.Set(r);

        t.Subtract(v[i]);

        std::cout << "Reference "
                  << i << ":    "
                  << t[0] << "    "
                  << t[1] << "    "
                  << t[2]
                  << std::endl << std::endl;

        tetBasis.ComputeBn(i, lc, bnValue);

        t.Set(bnValue[0], unit[0]);

        t.Add(bnValue[1], unit[1]);

        t.Add(bnValue[2], unit[2]);

        std::cout << "Basis Fn "
                  << i << ":    "
                  << t[0] << "    "
                  << t[1] << "    "
                  << t[2]
                  << std::endl << std::endl;

        tetBasis.ComputeDiv(i, lc, bnValue);

        std::cout << "Divergence "
                  << i << ":    "
                  << bnValue[0]
                  << std::endl << std::endl;

    }

    std::cout << "Test of basis function on tet is done!"
              << std::endl << std::endl;

    v[0].Set(0.0, 0.0, 0.0);
    v[1].Set(0.5, 0.0, 0.1);
    v[2].Set(0.6, 0.7, 0.2);
    v[3].Set(0.2, 0.8, 0.3);
    v[4].Set(-0.2, 0.1, 1.0);
    v[5].Set(1.0, 0.2, 0.9);
    v[6].Set(0.8, 0.8, 0.8);
    v[7].Set(0.2, 1.0, 0.7);

    std::cout << "Testing basis function on quad ..."
              << std::endl << std::endl;

    NovaBasis::DivBasisQuad quadBasis;

    NovaMesh::Quad quad;

    quad.Initialize(3, (const NovaType::R3 **) (av));

    quad.ComputeGlobalCoord(lc, r);

    quad.ComputeUnitaryVectors(lc, unit);

    for(unsigned i(0); i < quad.GetNumNodes(); ++i)
    {
        quadBasis.ComputeBn(i, lc, bnValue);

        t.Set(bnValue[0], unit[0]);

        t.Add(bnValue[1], unit[1]);

        std::cout << "Basis Fn "
                  << i << ":    "
                  << t[0] << "    "
                  << t[1] << "    "
                  << t[2]
                  << std::endl << std::endl;

        quadBasis.ComputeDiv(i, lc, bnValue);

        std::cout << "Divergence "
                  << i << ":    "
                  << bnValue[0]
                  << std::endl << std::endl;

    }

    std::cout << "Test of basis function on quad is done!"
              << std::endl << std::endl;

    std::cout << "Testing basis function on hex..."
              << std::endl << std::endl;

    NovaBasis::DivBasisHex hexBasis;

    NovaMesh::Hex hex;

    hex.Initialize(4, (const NovaType::R3 **) (av));

    hex.ComputeGlobalCoord(lc, r);

    hex.ComputeUnitaryVectors(lc, unit);

    for(unsigned i(0); i < 6; ++i)
    {
        hexBasis.ComputeBn(i, lc, bnValue);

        t.Set(bnValue[0], unit[0]);

        t.Add(bnValue[1], unit[1]);

        t.Add(bnValue[2], unit[2]);

        std::cout << "Basis Fn "
                  << i << ":    "
                  << t[0] << "    "
                  << t[1] << "    "
                  << t[2]
                  << std::endl << std::endl;

        hexBasis.ComputeDiv(i, lc, bnValue);

        std::cout << "Divergence "
                  << i << ":    "
                  << bnValue[0]
                  << std::endl << std::endl;

    }

    std::cout << "Test of basis function on hex is done!"
              << std::endl << std::endl;

    return 0;

}
