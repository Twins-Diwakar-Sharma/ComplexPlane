#include "projections.h"

float* projection::orthogonal = new float[16];

void projection::setOrthogonal(float l,float r,float b,float t,float n,float f)
{
    orthogonal[0] = 2.0f/(r-l);      orthogonal[4] = 0;      orthogonal[8] = 0;      orthogonal[12] = -(r+l)/(r-l);
    orthogonal[1] = 0;      orthogonal[5] = 2.0f/(t-b);      orthogonal[9] = 0;      orthogonal[13] = -(t+b)/(t-b);
    orthogonal[2] = 0;      orthogonal[6] = 0;      orthogonal[10] = -2.0f/(f-n);      orthogonal[14] = -(f+n)/(f-n);
    orthogonal[3] = 0;      orthogonal[7] = 0;      orthogonal[11] = 0;      orthogonal[15] = 1;

}

void projection::setOrthogonal(float f)
{
    setOrthogonal(-f,f,-f,f,-f,f);
}
