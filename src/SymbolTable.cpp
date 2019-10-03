#include "SymbolTable.h"

std::map<std::string,Identifier*> symbol::table;
std::string symbol::z;

void symbol::purge()
{
    for(std::map<std::string,Identifier*>::iterator it = table.begin(); it!=table.end(); ++it)
    {
        delete it->second;
    }
    table.clear();
}

void symbol::fetchId(std::string lex, bool* isZ, Identifier** pt)
{
    if(lex.compare(z) == 0)
        *isZ =  true;
    if(table.find(lex) == table.end())
    {
            Identifier* iden = new Identifier();
            if(!(*isZ))
                iden->pure = true;
            else
                iden->pure = false;
            table.insert(std::pair<std::string,Identifier*>(lex,iden));
            *pt = iden;
 //           std::cout << " new created " << std::endl;
    }
    else
    {
//            std::cout << "Already in table " << std::endl;
            *pt = table[lex];
    }
}

