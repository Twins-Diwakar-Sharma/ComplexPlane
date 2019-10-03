#ifndef H_TSTTS_H
#define H_TSTTS_H

#include <string>
#include <map>
#include <iostream>

struct Identifier
{
         std::string zStr="";
         float re=0;
         float im=0;
         bool pure=true;
};





namespace symbol
{
    extern std::map<std::string,Identifier*> table;
    extern std::string z;
    void purge();
    void fetchId(std::string,bool*,Identifier**);
}
#endif
