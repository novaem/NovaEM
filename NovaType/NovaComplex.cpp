#include "NovaComplex.h"

using namespace NovaType;

NovaComplex NovaType::operator +(const double &b,
                                 const NovaComplex &a)
{
    NovaComplex result(a);

    result += b;

    return result;
}

NovaComplex NovaType::operator +(const NovaComplex &a,
                                 const double &b)
{
    NovaComplex result(a);

    result += b;

    return result;
}

NovaComplex NovaType::operator +(const NovaComplex &a,
                                 const NovaComplex &b)
{
    NovaComplex result(a);

    result += b;

    return result;
}

NovaComplex NovaType::operator -(const double &b,
                                 const NovaComplex &a)
{
    NovaComplex result(b - a.m_real,
                       -a.m_imag);

    return result;
}

NovaComplex NovaType::operator -(const NovaComplex &a,
                                 const double &b)
{
    NovaComplex result(a);

    result -= b;

    return result;
}

NovaComplex NovaType::operator -(const NovaComplex &a,
                                 const NovaComplex &b)
{
    NovaComplex result(a);

    result -= b;

    return result;
}

NovaComplex NovaType::operator *(const double &b,
                                 const NovaComplex &a)
{
    NovaComplex result(a);

    result *= b;

    return result;
}

NovaComplex NovaType::operator *(const NovaComplex &a,
                                 const double &b)
{
    NovaComplex result(a);

    result *= b;

    return result;
}

NovaComplex NovaType::operator *(const NovaComplex &a,
                                 const NovaComplex &b)
{
    NovaComplex result(a);

    result *= b;

    return result;
}

NovaComplex NovaType::operator /(const double &b,
                                 const NovaComplex &a)
{
    NovaComplex result;

    a.Conjg(result);

    result *= b;

    result /= a.MagSq();

    return result;
}

NovaComplex NovaType::operator /(const NovaComplex &a,
                                 const double &b)
{
    NovaComplex result(a);

    result /= b;

    return result;
}

NovaComplex NovaType::operator /(const NovaComplex &a,
                                 const NovaComplex &b)
{
    NovaComplex result(a);

    result /= b;

    return result;
}
