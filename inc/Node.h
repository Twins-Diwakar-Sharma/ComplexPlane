#ifndef H_NODE_H
#define H_NODE_H

#include <string>
#include <Terminals.h>
#include <NonTerminals.h>

#define RED true
#define WHITE false

#define O_EQ 10
#define O_PL 21
#define O_MI 32
#define O_MU 43
#define O_DI 54

struct Node
{
    struct Element
    {
        std::string zStr="";
        float re=0, im=0;
        bool pure = true;
    };
    int type;
    Element inh, syn;
    int op = O_EQ;
    bool color = WHITE;
};


#endif
