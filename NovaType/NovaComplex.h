#ifndef NOVA_COMPLEX_H
#define NOVA_COMPLEX_H

#pragma once

#include <cmath>

namespace NovaType
{

    class NovaComplex
    {
    protected:

        double m_real;

        double m_imag;

    public:

        // Constructors:

        NovaComplex():
            m_real(0.0),
            m_imag(0.0)
        {}

        NovaComplex(const double &real):
            m_real(real),
            m_imag(0.0)
        {}

        NovaComplex(const double &real,
                    const double &imag):
            m_real(real),
            m_imag(imag)
        {}

        NovaComplex(const NovaComplex &data)
        {
            m_real = data.m_real;

            m_imag = data.m_imag;
        }

        // Single operand operators:

        const NovaComplex &operator =(const NovaComplex &data)
        {
            m_real = data.m_real;

            m_imag = data.m_imag;

            return *this;
        }

        void operator +=(const double &a)
        {
            m_real += a;
        }

        void operator +=(const NovaComplex &a)
        {
            m_real += a.m_real;

            m_imag += a.m_imag;
        }

        void operator -=(const double &a)
        {
            m_real -= a;
        }

        void operator -=(const NovaComplex &a)
        {
            m_real -= a.m_real;

            m_imag -= a.m_imag;
        }

        void operator *=(const double &a)
        {
            m_real *= a;

            m_imag *= a;
        }

        void operator *=(const NovaComplex &a)
        {
            double real = m_real * a.m_real -
                          m_imag * a.m_imag;

            double imag = m_real * a.m_imag +
                          m_imag * a.m_real;

            m_real = real;

            m_imag = imag;
        }

        void operator /=(const double &a)
        {
            m_real /= a;

            m_imag /= a;
        }

        void operator /=(const NovaComplex &a)
        {
            double real = m_real * a.m_real +
                          m_imag * a.m_imag;

            double imag = m_real * (-a.m_imag) +
                          m_imag * a.m_real;

            double mag2 = a.m_real * a.m_real +
                          a.m_imag * a.m_imag;

            m_real = real / mag2;

            m_imag = imag / mag2;

        }

        // Member functions fetch real and imaginary parts:

        double &Real()
        {
            return m_real;
        }

        const double &Real() const
        {
            return m_real;
        }

        double &Imag()
        {
            return m_imag;
        }

        const double &Imag() const
        {
            return m_imag;
        }

        // Compute the magnitude:

        double Mag() const
        {
            return std::sqrt(m_real * m_real +
                             m_imag * m_imag);
        }

        // Compute the squre of the magnitude:

        double MagSq() const
        {
            return m_real * m_real +
                   m_imag * m_imag;
        }

        // Flip the sign:

        void Negate()
        {
            m_real = -m_real;

            m_imag = -m_imag;
        }

        // Compute the congjugate:

        void Conjg(NovaComplex &result) const
        {
            result.m_real = m_real;

            result.m_imag = -m_imag;
        }

        // Less efficient version:

        NovaComplex Conjg() const
        {
            NovaComplex result(m_real,-m_imag);

            return result;
        }

        // Compute exp(a):

        void Exp(NovaComplex &result) const
        {
            result.m_real = std::cos(m_imag);

            result.m_imag = std::sin(m_imag);

            result *= std::exp(m_real);
        }

        // Compute exp(j * a):

        void ExpJ(NovaComplex &result) const
        {
            result.m_real = std::cos(m_real);

            result.m_imag = std::sin(m_real);

            result *= std::exp(-m_imag);
        }

        // Compute exp(-j * a):

        void ExpMJ(NovaComplex &result) const
        {
            result.m_real = std::cos(-m_real);

            result.m_imag = std::sin(-m_real);

            result *= std::exp(m_imag);
        }

        // Double operand operators.
        // These operators are less efficient and
        // should be avoided:

        friend NovaComplex operator +(const double &b,
                                      const NovaComplex &a);

        friend NovaComplex operator +(const NovaComplex &a,
                                      const double &b);

        friend NovaComplex operator +(const NovaComplex &a,
                                      const NovaComplex &b);

        friend NovaComplex operator -(const double &b,
                                      const NovaComplex &a);

        friend NovaComplex operator -(const NovaComplex &a,
                                      const double &b);

        friend NovaComplex operator -(const NovaComplex &a,
                                      const NovaComplex &b);

        friend NovaComplex operator *(const double &b,
                                      const NovaComplex &a);

        friend NovaComplex operator *(const NovaComplex &a,
                                      const double &b);

        friend NovaComplex operator *(const NovaComplex &a,
                                      const NovaComplex &b);

        friend NovaComplex operator /(const double &b,
                                      const NovaComplex &a);

        friend NovaComplex operator /(const NovaComplex &a,
                                      const double &b);

        friend NovaComplex operator /(const NovaComplex &a,
                                      const NovaComplex &b);

    };

    NovaComplex operator +(const double &b,
                                  const NovaComplex &a);

    NovaComplex operator +(const NovaComplex &a,
                                  const double &b);

    NovaComplex operator +(const NovaComplex &a,
                                  const NovaComplex &b);

    NovaComplex operator -(const double &b,
                                  const NovaComplex &a);

    NovaComplex operator -(const NovaComplex &a,
                                  const double &b);

    NovaComplex operator -(const NovaComplex &a,
                                  const NovaComplex &b);

    NovaComplex operator *(const double &b,
                                  const NovaComplex &a);

    NovaComplex operator *(const NovaComplex &a,
                                  const double &b);

    NovaComplex operator *(const NovaComplex &a,
                                  const NovaComplex &b);

    NovaComplex operator /(const double &b,
                                  const NovaComplex &a);

    NovaComplex operator /(const NovaComplex &a,
                                  const double &b);

    NovaComplex operator /(const NovaComplex &a,
                                  const NovaComplex &b);


}
#endif // NOVA_COMPLEX_H
