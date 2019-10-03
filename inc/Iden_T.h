#ifndef H_IDENTIFIER_TOKEN_H
#define H_IDENTIFIER_TOKEN_H

#include "Token.h"

class Iden_T : public Token
{
    private:
        std::string lexeme;
    public:
        std::string& getLexeme();
        Iden_T(std::string&);

};

#endif
