#include "Token.h"

Token::Token(int type)
{
    this->type = type;
}

int Token::getType()
{
    return type;
}

void Token::discard()
{
    this->type = ERR;
}
