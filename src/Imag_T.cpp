#include "Imag_T.h"

Imag_T::Imag_T(std::string lexeme) : Token(IMAG)
{
    value = 0;
    bool beforeDot = true;
    float exp = 1.0f;
    if(lexeme.size() == 1)
    {
        lexeme = std::string("1");
    }
    else if( lexeme[0] == 'i')
    {
        lexeme = lexeme.substr(1,lexeme.size()-1);
   }
    else
    {
        lexeme = lexeme.substr(0,lexeme.size()-1);
    }

         for(int i = 0; i<lexeme.size(); i++)
        {
            if(lexeme[i] == '.')
            {
                beforeDot = false;
            }
            else
            {
                if(beforeDot)
                {
                    int dig = ((int)(lexeme[i]) - 48);
                    value = value*10 + (float)(dig);
                }
                else
                {
                    int dig = ((int)(lexeme[i]) - 48);
                    exp = exp*0.1f;
                    value = (  (float)dig ) * exp + value;
                }
            }
       }
}

float Imag_T::getValue()
{
    return value;
}
