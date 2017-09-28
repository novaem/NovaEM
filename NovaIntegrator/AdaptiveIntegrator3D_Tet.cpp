#include "GaussRule3D_Tet.h"
#include "FixedPntIntegrator3D_Tet.h"
#include "AdaptiveIntegrator3D_Tet.h"
using namespace NovaIntegrator;

const unsigned
AdaptiveIntegrator3D_Tet::NUM_VERTEX = 4;

const unsigned
AdaptiveIntegrator3D_Tet::DIM = NovaDef::DIM_3D;

const unsigned
AdaptiveIntegrator3D_Tet::BOUND_REC_LENGTH =
        AdaptiveIntegrator3D_Tet::NUM_VERTEX *
        AdaptiveIntegrator3D_Tet::DIM;

AdaptiveIntegrator3D_Tet::
AdaptiveIntegrator3D_Tet(const unsigned order) : AdaptiveIntegrator()
{
    InitializeRule(2);

    m_rule[0] = GaussRule3D_Tet::GetInstance(order);

    m_rule[1] = GaussRule3D_Tet::GetNextOrderInstance(order);

    m_fixedPntIntegrator = new FixedPntIntegrator3D_Tet;

    m_numDomains = 1;

    unsigned length = BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

AdaptiveIntegrator3D_Tet::~AdaptiveIntegrator3D_Tet()
{
}

void AdaptiveIntegrator3D_Tet::SetNumDomain(unsigned numDomain)
{
    m_numDomains = numDomain;

    unsigned length = numDomain * BOUND_REC_LENGTH;

    InitializeBoundSpace(length);
}

void AdaptiveIntegrator3D_Tet::SetOrder(const unsigned order)
{
    m_rule[0] = GaussRule3D_Tet::GetInstance(order);

    m_rule[1] = GaussRule3D_Tet::GetNextOrderInstance(order);
}

unsigned AdaptiveIntegrator3D_Tet::GetBoundRecLength() const
{
    return BOUND_REC_LENGTH;
}

unsigned AdaptiveIntegrator3D_Tet::GetSplitDomainNum() const
{
    return 8;
}

void AdaptiveIntegrator3D_Tet::
SplitDomain(double *oldDomain,
            double *newDomain,
            unsigned splitDirection)
{
    double &X1 = oldDomain[0];
    double &Y1 = oldDomain[1];
    double &Z1 = oldDomain[2];

    double &X2 = oldDomain[3];
    double &Y2 = oldDomain[4];
    double &Z2 = oldDomain[5];

    double &X3 = oldDomain[6];
    double &Y3 = oldDomain[7];
    double &Z3 = oldDomain[8];

    double &X4 = oldDomain[9];
    double &Y4 = oldDomain[10];
    double &Z4 = oldDomain[11];

    // Bisect each edges of Tet:

    double midPointX1 = (X1 + X2) * 0.5;
    double midPointY1 = (Y1 + Y2) * 0.5;
    double midPointZ1 = (Z1 + Z2) * 0.5;

    double midPointX2 = (X2 + X3) * 0.5;
    double midPointY2 = (Y2 + Y3) * 0.5;
    double midPointZ2 = (Z2 + Z3) * 0.5;

    double midPointX3 = (X1 + X3) * 0.5;
    double midPointY3 = (Y1 + Y3) * 0.5;
    double midPointZ3 = (Z1 + Z3) * 0.5;

    double midPointX4 = (X1 + X4) * 0.5;
    double midPointY4 = (Y1 + Y4) * 0.5;
    double midPointZ4 = (Z1 + Z4) * 0.5;

    double midPointX5 = (X2 + X4) * 0.5;
    double midPointY5 = (Y2 + Y4) * 0.5;
    double midPointZ5 = (Z2 + Z4) * 0.5;

    double midPointX6 = (X3 + X4) * 0.5;
    double midPointY6 = (Y3 + Y4) * 0.5;
    double midPointZ6 = (Z3 + Z4) * 0.5;

    // Split the Tet into 8 subTet:

    //Tet 1:
    newDomain[0] = X1;
    newDomain[1] = Y1;
    newDomain[2] = Z1;

    newDomain[3] = midPointX1;
    newDomain[4] = midPointY1;
    newDomain[5] = midPointZ1;

    newDomain[6] = midPointX3;
    newDomain[7] = midPointY3;
    newDomain[8] = midPointZ3;

    newDomain[9] = midPointX4;
    newDomain[10] = midPointY4;
    newDomain[11] = midPointZ4;

    //Tet 2:
    newDomain[12] = midPointX1;
    newDomain[13] = midPointY1;
    newDomain[14] = midPointZ1;

    newDomain[15] = X2;
    newDomain[16] = Y2;
    newDomain[17] = Z2;

    newDomain[18] = midPointX2;
    newDomain[19] = midPointY2;
    newDomain[20] = midPointZ2;

    newDomain[21] = midPointX5;
    newDomain[22] = midPointY5;
    newDomain[23] = midPointZ5;

    //Tet 3:
    newDomain[24] = midPointX3;
    newDomain[25] = midPointY3;
    newDomain[26] = midPointZ3;

    newDomain[27] = midPointX2;
    newDomain[28] = midPointY2;
    newDomain[29] = midPointZ2;

    newDomain[30] = X3;
    newDomain[31] = Y3;
    newDomain[32] = Z3;

    newDomain[33] = midPointX6;
    newDomain[34] = midPointY6;
    newDomain[35] = midPointZ6;

    //Tet 4:
    newDomain[36] = midPointX4;
    newDomain[37] = midPointY4;
    newDomain[38] = midPointZ4;

    newDomain[39] = midPointX5;
    newDomain[40] = midPointY5;
    newDomain[41] = midPointZ5;

    newDomain[42] = midPointX6;
    newDomain[43] = midPointY6;
    newDomain[44] = midPointZ6;

    newDomain[45] = X4;
    newDomain[46] = Y4;
    newDomain[47] = Z4;

    //Tet 5:
    newDomain[48] = midPointX1;
    newDomain[49] = midPointY1;
    newDomain[50] = midPointZ1;

    newDomain[51] = midPointX4;
    newDomain[52] = midPointY4;
    newDomain[53] = midPointZ4;

    newDomain[54] = midPointX5;
    newDomain[55] = midPointY5;
    newDomain[56] = midPointZ5;

    newDomain[57] = midPointX3;
    newDomain[58] = midPointY3;
    newDomain[59] = midPointZ3;

    //Tet 6:
    newDomain[60] = midPointX1;
    newDomain[61] = midPointY1;
    newDomain[62] = midPointZ1;

    newDomain[63] = midPointX5;
    newDomain[64] = midPointY5;
    newDomain[65] = midPointZ5;

    newDomain[66] = midPointX2;
    newDomain[67] = midPointY2;
    newDomain[68] = midPointZ2;

    newDomain[69] = midPointX3;
    newDomain[70] = midPointY3;
    newDomain[71] = midPointZ3;

    //Tet 7:
    newDomain[72] = midPointX6;
    newDomain[73] = midPointY6;
    newDomain[74] = midPointZ6;

    newDomain[75] = midPointX3;
    newDomain[76] = midPointY3;
    newDomain[77] = midPointZ3;

    newDomain[78] = midPointX2;
    newDomain[79] = midPointY2;
    newDomain[80] = midPointZ2;

    newDomain[81] = midPointX5;
    newDomain[82] = midPointY5;
    newDomain[83] = midPointZ5;

    //Tet 8:
    newDomain[84] = midPointX6;
    newDomain[85] = midPointY6;
    newDomain[86] = midPointZ6;

    newDomain[87] = midPointX4;
    newDomain[88] = midPointY4;
    newDomain[89] = midPointZ4;

    newDomain[90] = midPointX3;
    newDomain[91] = midPointY3;
    newDomain[92] = midPointZ3;

    newDomain[93] = midPointX5;
    newDomain[94] = midPointY5;
    newDomain[95] = midPointZ5;
 }
