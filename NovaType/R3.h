#ifndef R3_H
#define R3_H

#pragma once

#include <cmath>

namespace NovaType
{
    class R3
    {
    protected:

        double m_coord[3];

    public:

        R3()
        {
            m_coord[0] = 0.0;

            m_coord[1] = 0.0;

            m_coord[2] = 0.0;
        }

        R3(const double &x,
           const double &y,
           const double &z)
        {
            m_coord[0] = x;

            m_coord[1] = y;

            m_coord[2] = z;
        }

        R3(const double *coord)
        {
            m_coord[0] = coord[0];

            m_coord[1] = coord[1];

            m_coord[2] = coord[2];
        }

        R3(const R3 &data)
        {
            m_coord[0] = data.m_coord[0];

            m_coord[1] = data.m_coord[1];

            m_coord[2] = data.m_coord[2];
        }

        const R3 &operator =(const R3 &data)
        {
            m_coord[0] = data.m_coord[0];

            m_coord[1] = data.m_coord[1];

            m_coord[2] = data.m_coord[2];

            return *this;
        }

        double &operator [](const unsigned i)
        {
            return m_coord[i];
        }

        const double &operator [](const unsigned i) const
        {
            return m_coord[i];
        }

        const R3 &operator +=(const R3 &data)
        {
            m_coord[0] += data.m_coord[0];

            m_coord[1] += data.m_coord[1];

            m_coord[2] += data.m_coord[2];

            return *this;
        }

        const R3 &operator -=(const R3 &data)
        {
            m_coord[0] -= data.m_coord[0];

            m_coord[1] -= data.m_coord[1];

            m_coord[2] -= data.m_coord[2];

            return *this;
        }

        const R3 &operator *=(const double &a)
        {
            m_coord[0] *= a;

            m_coord[1] *= a;

            m_coord[2] *= a;

            return *this;
        }

        const R3 &operator /=(const double &a)
        {
            m_coord[0] /= a;

            m_coord[1] /= a;

            m_coord[2] /= a;

            return *this;
        }

        double &GetCoord(const unsigned i)
        {
            return m_coord[i];
        }

        double *GetCoord()
        {
            return m_coord;
        }

        const double &GetCoord(const unsigned i) const
        {
            return m_coord[i];
        }

        const double *GetCoord() const
        {
            return m_coord;
        }

        double Mag() const
        {
            return std::sqrt(m_coord[0] * m_coord[0] +
                             m_coord[1] * m_coord[1] +
                             m_coord[2] * m_coord[2]);
        }

        void Normalize()
        {
            double norm = Mag();

            m_coord[0] /= norm;

            m_coord[1] /= norm;

            m_coord[2] /= norm;
        }

        void Negate()
        {
            m_coord[0] = -m_coord[0];

            m_coord[1] = -m_coord[1];

            m_coord[2] = -m_coord[2];
        }

        double Dot(const R3 &data) const
        {
            double result = m_coord[0] * data.m_coord[0];

            result += m_coord[1] * data.m_coord[1];

            result += m_coord[2] * data.m_coord[2];

            return result;
        }

        void Cross(const R3 &data, R3 &result) const
        {
            result.m_coord[0] = m_coord[1] * data.m_coord[2] -
                                m_coord[2] * data.m_coord[1];

            result.m_coord[1] = m_coord[2] * data.m_coord[0] -
                                m_coord[0] * data.m_coord[2];

            result.m_coord[2] = m_coord[0] * data.m_coord[1] -
                                m_coord[1] * data.m_coord[0];
        }

        R3 Cross(const R3 &data) const
        {
            return R3(m_coord[1] * data.m_coord[2] -
                      m_coord[2] * data.m_coord[1],

                      m_coord[2] * data.m_coord[0] -
                      m_coord[0] * data.m_coord[2],

                      m_coord[0] * data.m_coord[1] -
                      m_coord[1] * data.m_coord[0]);
        }

        double ComputeDistance(const R3 &data) const
        {
            double distance(0.0);

            double d(0.0);

            d = m_coord[0] - data.m_coord[0];
            d *= d;

            distance += d;

            d = m_coord[1] - data.m_coord[1];
            d *= d;

            distance += d;

            d = m_coord[2] - data.m_coord[2];
            d *= d;

            distance += d;

            return std::sqrt(distance);
        }

        friend const R3 operator +(const R3 &a, const R3 &b);
        friend const R3 operator -(const R3 &a, const R3 &b);
        friend const R3 operator *(const R3 &data, const double &a);
        friend const R3 operator *(const double &a, const R3 &data);
        friend const R3 operator /(const R3 &data, const double &a);

    };

    const R3 operator +(const R3 &a, const R3 &b);
    const R3 operator -(const R3 &a, const R3 &b);
    const R3 operator *(const R3 &data, const double &a);
    const R3 operator *(const double &a, const R3 &data);
    const R3 operator /(const R3 &data, const double &a);

}

#endif // R3_H
