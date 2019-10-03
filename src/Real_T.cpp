#include "Real_T.h"

Real_T::Real_T(std::string lexeme) : Token(REAL)
{
    bool beforeDot = true;
    float exp = 1.0f;
    value = 0;
    for(int i=0; i<lexeme.size(); i++)
    {
        if(lexeme[i] == '.')
        {
            beforeDot = false;
        }
        else
        {
            if(beforeDot)
            {
                int dig = (int)(lexeme[i]) - 48;
                value = (float)(dig) + value*10;
            }
            else
            {
                int dig = (int)(lexeme[i]) - 48;
                exp = exp*0.1f;
                value = ( (float)(dig) ) * exp + value;
            }
        }
    }
}

float Real_T::getValue()
{
    return value;
}
