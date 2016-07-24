#include <iostream>
#include "NovaComplex.h"
#include "TestComplex.h"

int TestComplex()
{

    std::cout << "Testing complex calculation ..." << std::endl;

    NovaType::NovaComplex a(1), b(3, 4);

    a.Imag() = 2.0;

    NovaType::NovaComplex c(a);

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = b;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c += 5;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c -= 5;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c += a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c -= a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a;

    c *= 2.0;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c /= 2.0;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a;

    c *= b;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c /= b;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    std::cout << b.Mag() << std::endl;

    c.Negate();

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c.Negate();

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    a.Conjg(c);

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = c.Conjg();

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    a.Exp(c);

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    a.ExpJ(c);

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    a.ExpMJ(c);

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a + 5;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = 5 + a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a + b;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a - 5;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = 5 - a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = b - a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = 5 * a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a * 5;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a * b;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = a / 5;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = 5 / a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    c = b / a;

    std::cout << c.Real() << "    "
              << c.Imag() << std::endl;

    std::cout << "Complex calculation test is done."
              << std::endl << std::endl;

    return 0;
}
