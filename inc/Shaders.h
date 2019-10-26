#ifndef H_SHADERS_H
#define H_SHADERS_H

#include <string>
#include <iostream>
#include <vector>
namespace shaders
{
    extern std::string grid_vs;
    extern std::string grid_gs;
    extern std::string grid_fs;

    void updateGridShader(std::string*);
}

#endif
