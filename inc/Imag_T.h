#ifndef H_IMAGINARY_TOKEN_H
#define H_IMAGINARY_TOKEN_H

#include "Token.h"

class Imag_T : public Token
{
    private:
        float value;
    public:
        Imag_T(std::string);
        float getValue();
};

#endif
