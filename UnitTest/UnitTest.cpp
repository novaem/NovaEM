#include "TestR3.h"
#include "TestComplex.h"
#include "TestPatch.h"
#include "TestBasis.h"
#include "TestIntegrator.h"

int main()
{
    TestR3();

    TestComplex();

    TestPatch();

    TestBasis();

    IntTester intTester;

    intTester.TestRule();

    intTester.TestIntegrator();

    return 0;
}
