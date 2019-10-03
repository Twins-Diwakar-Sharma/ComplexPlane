#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include "allGL.h"
#include <map>
#include <string>
#include <iostream>

class ShaderProgram
{
    private:
        unsigned int programID;
        unsigned int vertexID;
        unsigned int geometryID;
        unsigned int fragmentID;
        std::map<std::string,int> uniformMap;
        void createShader(unsigned int&, int, std::string&);

    public:
        ShaderProgram();
        ~ShaderProgram();

        void compileAndLink(std::string&,std::string&);
        void compileAndLink(std::string&,std::string&,std::string&);
        void mapUniform(std::string);
        void setUniform(std::string,float*);
        void setUniform(std::string,float);
        void clearUniforms();
        void use();
        void unuse();
};

#endif
