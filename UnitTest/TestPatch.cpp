#include "TestPatch.h"
#include "Triangle.h"
#include "Tet.h"
#include "Quad.h"
#include "Hex.h"
#include <iostream>

int TestPatch()
{
    NovaType::R3 v[8];

    const NovaType::R3 *av[8];

    v[0].Set(0.0, 0.0, 0.0);
    v[1].Set(1.0, 0.0, 0.0);
    v[2].Set(1.0, 1.0, 0.0);
    v[3].Set(0.0, 1.0, 0.0);
    v[4].Set(0.0, 0.0, 1.0);
    v[5].Set(1.0, 0.0, 1.0);
    v[6].Set(1.0, 1.0, 1.0);
    v[7].Set(0.0, 1.0, 1.0);

    av[0] = &v[0];

    av[1] = &v[1];

    av[2] = &v[2];

    av[3] = &v[3];

    av[4] = &v[4];

    av[5] = &v[5];

    av[6] = &v[6];

    av[7] = &v[7];

    double lc[] = {1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0};

    NovaType::R3 t1;

    NovaType::R3 unit[3];

    std::cout << "Testing Triangle ..."
              << std::endl << std::endl;

    NovaMesh::Triangle triangle;

    triangle.Initialize(0, (const NovaType::R3 **) (av));

    std::cout << "Type: "
              << triangle.GetType()
              << std::endl
              << std::endl;

    triangle.ComputeGlobalCoord(lc, t1);

    std::cout << "Global coordinate: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    double a = triangle.ComputeJacobian(lc);

    std::cout << "Jacobian: " << a
              << std::endl << std::endl;

    triangle.ComputeNormalDir(lc, t1);

    std::cout << "Normal direction: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    triangle.ComputeUnitaryVectors(lc, unit);

    unsigned long n = triangle.GetDimension();

    for(unsigned i(0); i < n; ++i)
    {
        t1.Set(unit[i]);

        std::cout << "Unitary vector " << i << ": "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }


    t1.Set(triangle.GetCenter());

    std::cout << "Center: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = triangle.GetID();

    std::cout << "ID: " << n << std::endl << std::endl;

    n = triangle.GetNumNodes();

    std::cout << "# of nodes: " << n << std::endl << std::endl;

    for(unsigned i(0); i < n; ++i)
    {

        t1.Set(*triangle.GetNode(i));

        std::cout << "Node " << i << "  : "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    std::cout << "Triangle test is done!"
              << std::endl << std::endl;

    v[0].Set(0.0, 0.0, 0.0);
    v[1].Set(1.0, 0.0, 0.0);
    v[2].Set(0.0, 1.0, 0.0);
    v[3].Set(0.0, 0.0, 1.0);

    std::cout << "Testing Tet ..."
              << std::endl << std::endl;

    NovaMesh::Tet tet;

    tet.Initialize(2, (const NovaType::R3 **) (av));

    std::cout << "Type: "
              << tet.GetType()
              << std::endl
              << std::endl;

    tet.ComputeGlobalCoord(lc, t1);

    std::cout << "Global coordinate: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    a = tet.ComputeJacobian(lc);

    std::cout << "Jacobian: " << a
              << std::endl << std::endl;

    tet.ComputeUnitaryVectors(lc, unit);

    n = tet.GetDimension();

    for(unsigned i(0); i < n; ++i)
    {
        t1.Set(unit[i]);

        std::cout << "Unitary vector " << i << ": "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    t1.Set(tet.GetCenter());

    std::cout << "Center: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = tet.GetID();

    std::cout << "ID: " << n << std::endl << std::endl;

    n = tet.GetNumNodes();

    std::cout << "# of nodes: " << n << std::endl << std::endl;

    for(unsigned i(0); i < n; ++i)
    {

        t1.Set(*tet.GetNode(i));

        std::cout << "Node " << i << "  : "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    std::cout << "Tet test is done!"
              << std::endl << std::endl;

    v[0].Set(0.0, 0.0, 0.0);
    v[1].Set(1.0, 0.0, 0.0);
    v[2].Set(1.0, 1.0, 0.0);
    v[3].Set(0.0, 1.0, 0.0);
    v[4].Set(0.0, 0.0, 1.0);
    v[5].Set(1.0, 0.0, 1.0);
    v[6].Set(1.0, 1.0, 1.0);
    v[7].Set(0.0, 1.0, 1.0);

    NovaMesh::Quad quad;

    quad.Initialize(3, (const NovaType::R3 **) (av));

    std::cout << "Type: "
              << quad.GetType()
              << std::endl
              << std::endl;

    quad.ComputeGlobalCoord(lc, t1);

    std::cout << "Testing Quad ..."
              << std::endl << std::endl;

    std::cout << "Global coordinate: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    a = quad.ComputeJacobian(lc);

    std::cout << "Jacobian: " << a
              << std::endl << std::endl;

    quad.ComputeNormalDir(lc, t1);

    std::cout << "Normal direction: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    quad.ComputeUnitaryVectors(lc, unit);

    n = quad.GetDimension();

    for(unsigned i(0); i < n; ++i)
    {
        t1.Set(unit[i]);

        std::cout << "Unitary vector " << i << ": "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    t1.Set(quad.GetCenter());

    std::cout << "Center: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = quad.GetID();

    std::cout << "ID: " << n << std::endl << std::endl;

    n = quad.GetNumNodes();

    std::cout << "# of nodes: " << n << std::endl << std::endl;

    for(unsigned i(0); i < n; ++i)
    {

        t1.Set(*quad.GetNode(i));

        std::cout << "Node " << i << "  : "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    std::cout << "Distance between triangle and quad is: "
              << quad.ComputeDistance(triangle)
              << std::endl << std::endl;

    std::cout << "Quad test is done!"
              << std::endl << std::endl;

    NovaMesh::Hex hex;

    hex.Initialize(4, (const NovaType::R3 **) (av));

    std::cout << "Testing Hex ..."
              << std::endl << std::endl;

    std::cout << "Type: "
              << hex.GetType()
              << std::endl
              << std::endl;

    hex.ComputeGlobalCoord(lc, t1);

    std::cout << "Global coordinate: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    a = hex.ComputeJacobian(lc);

    std::cout << "Jacobian: " << a
              << std::endl << std::endl;

    hex.ComputeUnitaryVectors(lc, unit);

    n = tet.GetDimension();

    for(unsigned i(0); i < n; ++i)
    {
        t1.Set(unit[i]);

        std::cout << "Unitary vector " << i << ": "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    t1.Set(hex.GetCenter());

    std::cout << "Center: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = hex.GetID();

    std::cout << "ID: " << n << std::endl << std::endl;

    n = hex.GetNumNodes();

    std::cout << "# of nodes: " << n << std::endl << std::endl;

    for(unsigned i(0); i < n; ++i)
    {

        t1.Set(*hex.GetNode(i));

        std::cout << "Node " << i << "  : "
                  << t1[0] << "    "
                  << t1[1] << "    "
                  << t1[2]
                  << std::endl << std::endl;
    }

    std::cout << "Hex test is done!"
              << std::endl << std::endl;

    return 0;
}
