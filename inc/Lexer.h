#ifndef H_LEX_LOTHOR_H
#define H_LEX_LOTHOR_H

#include <iostream>
#include <string>
#include <vector>

#include "OneToken.h"

#define c_digit 0
#define c_alph 1
#define c_im 2
#define c_op 3
#define c_dot 4
#define c_ws 5
#define c_newline 6


class Lexer
{
    private:
        int pos=0;
        int startPos = 0;
        std::string* buffer;
        int state=0;
        int line=0;
        bool endofline = false;
    public:
        Lexer();
        ~Lexer();
        void reset(std::string*);
        int getPos();
        void tokenLine();  // temporary using int for token
        bool endOfLine();
        std::vector<Token*> tokens;
};

#endif
