#include "R3.h"

using namespace NovaType;

const R3 NovaType::operator +(const R3 &a, const R3 &b)
{
    R3 result(a);

    result += b;

    return result;
}

const R3 NovaType::operator -(const R3 &a, const R3 &b)
{
    R3 result(a);

    result -= b;

    return result;
}

const R3 NovaType::operator *(const R3 &data, const double &a)
{
    R3 result(data);

    result *= a;

    return result;
}

const R3 NovaType::operator *(const double &a, const R3 &data)
{
    R3 result(data);

    result *= a;

    return result;
}

const R3 NovaType::operator /(const R3 &data, const double &a)
{
    R3 result(data);

    result /= a;

    return result;
}

