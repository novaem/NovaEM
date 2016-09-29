#include "TestPatch.h"
#include "Triangle.h"
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

    NovaType::R3 t1, t2;

    NovaType::R3 unit[3];

    NovaMesh::Triangle triangle;

    triangle.Initialize(0, (const NovaType::R3 **) (av));

    triangle.ComputeGlobalCoord(lc, t1);

    std::cout << "Testing Triangle ..."
              << std::endl << std::endl;

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

    t1.Set(unit[0]);

    std::cout << "Unitary vector 1: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(unit[1]);

    std::cout << "Unitary vector 2: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(triangle.GetCenter());

    std::cout << "Center: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    unsigned long n = triangle.GetID();

    std::cout << "ID: " << n << std::endl << std::endl;

    t1.Set(*triangle.GetNode(0));

    std::cout << "Node 0: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(*triangle.GetNode(1));

    std::cout << "Node 1: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(*triangle.GetNode(2));

    std::cout << "Node 2: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = triangle.GetNumNodes();

    std::cout << "# of nodes: " << n << std::endl << std::endl;

    std::cout << "Type: "
              << triangle.GetType()
              << std::endl
              << std::endl;

    std::cout << "Triangle test is done!"
              << std::endl << std::endl;

    NovaMesh::Quad quad;

    quad.Initialize(1, (const NovaType::R3 **) (av));

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

    t1.Set(unit[0]);

    std::cout << "Unitary vector 1: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(unit[1]);

    std::cout << "Unitary vector 2: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(quad.GetCenter());

    std::cout << "Center: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = quad.GetID();

    std::cout << "ID: " << n << std::endl << std::endl;

    t1.Set(*quad.GetNode(0));

    std::cout << "Node 0: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(*quad.GetNode(1));

    std::cout << "Node 1: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(*quad.GetNode(2));

    std::cout << "Node 2: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(*quad.GetNode(3));

    std::cout << "Node 3: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    n = quad.GetNumNodes();

    std::cout << "# of nodes: " << n << std::endl << std::endl;

    std::cout << "Type: "
              << quad.GetType()
              << std::endl
              << std::endl;

    std::cout << "Distance between two patches is: "
              << quad.ComputeDistance(triangle)
              << std::endl << std::endl;

    std::cout << "Quad test is done!"
              << std::endl << std::endl;

    NovaMesh::Hex hex;

    hex.Initialize(1, (const NovaType::R3 **) (av));

    hex.ComputeGlobalCoord(lc, t1);

    std::cout << "Testing Hex ..."
              << std::endl << std::endl;

    std::cout << "Global coordinate: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    a = hex.ComputeJacobian(lc);

    std::cout << "Jacobian: " << a
              << std::endl << std::endl;

    hex.ComputeUnitaryVectors(lc, unit);

    t1.Set(unit[0]);

    std::cout << "Unitary vector 1: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(unit[1]);

    std::cout << "Unitary vector 2: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

    t1.Set(unit[2]);

    std::cout << "Unitary vector 3: "
              << t1[0] << "    "
              << t1[1] << "    "
              << t1[2]
              << std::endl << std::endl;

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
