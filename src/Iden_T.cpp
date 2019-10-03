#include "Iden_T.h"

Iden_T::Iden_T(std::string& lexeme) : Token(IDEN)
{
    this->lexeme = lexeme;
}

std::string& Iden_T::getLexeme()
{
    return lexeme;
}

