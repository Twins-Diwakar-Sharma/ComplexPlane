#ifndef H_PARSER_H
#define H_PARSER_H

#include "SymbolTable.h"
#include "Lexer.h"
#include "Stack.h"

//typedef void (*(prod_ptr)(void);

class Parser
{
    private:
        int tokenIndex=0;
        Lexer* lexer;
        Stack stac;
        typedef void (Parser::*prod_ptr)(void);
        int table[9][11];

        void fM();
        void fX0(); void fX1();
        void fE();
        void fE_0(); void fE_1(); void fE_2();
        void fT();
        void fT_0(); void fT_1(); void fT_2();
        void fF0(); void fF1(); void fF2(); void fF3();
        void fY0(); void fY1();
        void fH0(); void fH1();

        void fPlus();
        void fMinus();
        void fMultiply();
        void fDivide();
        void fLB();
        void fRB();
        void fIden();
        void fDollar();
        void fEqual();
        void fReal();
        void fImag();

        void initTable();
        int getProd(int NonT, int Term);

        Identifier* finalZ;
        Identifier* currID; // per line
        std::string currIDLex;
        bool end = false;
        int line=1;

    public:
        Parser();
       ~Parser();
       void display();
       bool parseAndTranslate(std::string*);
       prod_ptr prod[19];
       void reset(std::string*,std::string);
};

#endif
