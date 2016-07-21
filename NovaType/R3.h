#ifndef __R3__
#define __R3__

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
            *this = data;
        }

        const R3 &operator =(const R3 &data)
        {
            this->m_coord[0] = data.m_coord[0];

            this->m_coord[1] = data.m_coord[1];

            this->m_coord[2] = data.m_coord[2];

            return *this;
        }

        const R3 &operator +=(const R3 &data)
        {
            this->m_coord[0] += data.m_coord[0];

            this->m_coord[1] += data.m_coord[1];

            this->m_coord[2] += data.m_coord[2];

            return *this;
        }

        const R3 &operator -=(const R3 &data)
        {
            this->m_coord[0] -= data.m_coord[0];

            this->m_coord[1] -= data.m_coord[1];

            this->m_coord[2] -= data.m_coord[2];

            return *this;
        }

        const R3 &operator *=(const double &a)
        {
            this->m_coord[0] *= a;

            this->m_coord[1] *= a;

            this->m_coord[2] *= a;

            return *this;
        }

        const R3 &operator /=(const double &a)
        {
            this->m_coord[0] /= a;

            this->m_coord[1] /= a;

            this->m_coord[2] /= a;

            return *this;
        }

        double &operator [](const unsigned i)
        {
            return this->m_coord[i];
        }

        const double &GetCoord(const unsigned i)
        {
            return this->m_coord[i];
        }

        double Dot(const R3 &data)
        {
            double result = m_coord[0] * data.m_coord[0];

            result += m_coord[1] * data.m_coord[1];

            result += m_coord[2] * data.m_coord[2];
        }

        void Cross(const R3 &data, R3 &result)
        {
            result.m_coord[0] = m_coord[1] * data.m_coord[2] -
                                m_coord[2] * data.m_coord[1];

            result.m_coord[1] = m_coord[2] * data.m_coord[0] -
                                m_coord[0] * data.m_coord[2];

            result.m_coord[2] = m_coord[0] * data.m_coord[1] -
                                m_coord[1] * data.m_coord[0];
        }

        R3 Cross(const R3 &data)
        {
            return R3(m_coord[1] * data.m_coord[2] -
                      m_coord[2] * data.m_coord[1],

                      m_coord[2] * data.m_coord[0] -
                      m_coord[0] * data.m_coord[2],

                      m_coord[0] * data.m_coord[1] -
                      m_coord[1] * data.m_coord[0]);
        }

        friend R3 operator *(const R3 &data, const double &a);
        friend R3 operator *(const double &a, const R3 &data);
        friend R3 operator /(const R3 &data, const double &a);

    };

    R3 operator *(const R3 &data, const double &a)
    {
        R3 result(data);

        result *= a;

        return result;
    }

    R3 operator *(const double &a, const R3 &data)
    {
        R3 result(data);

        result *= a;

        return result;
    }

    R3 operator /(const R3 &data, const double &a)
    {
        R3 result(data);

        result /= a;

        return result;
    }


};

#endif
