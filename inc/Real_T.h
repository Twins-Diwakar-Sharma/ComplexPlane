#ifndef H_REAL_TOKEN_H
#define H_REAL_TOKEN_H

#include "Token.h"

class Real_T : public Token
{
    private:
        float value;
    public:
        Real_T(std::string);
        float getValue();

};

#endif
