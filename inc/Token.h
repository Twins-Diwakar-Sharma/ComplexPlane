#ifndef H_TOKEN_H
#define H_TOKEN_H

#include <string>
#include <Terminals.h>

class Token
{
    private:
        int type;
    public:
        Token(int);
        int getType();
        void discard();

};


#endif
