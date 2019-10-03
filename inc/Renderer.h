#ifndef H_RENDERER_H
#define H_RENDERER_H

#include "ShaderProgram.h"
#include "Grid.h"
#include "projections.h"
class Renderer
{
    private:
        ShaderProgram shader;
        void mapAllUniforms();
        void clearUniforms();
    public:
        void render(Grid&);
        Renderer();
        ~Renderer();
        void linkCode(std::string&,std::string&);
        void linkCode(std::string&,std::string&,std::string&);
};

#endif
