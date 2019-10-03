#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::linkCode(std::string& vertexCode, std::string& fragmentCode)
{
    clearUniforms();
    shader.compileAndLink(vertexCode,fragmentCode);
    mapAllUniforms();
}

void Renderer::linkCode(std::string& vertexCode, std::string& geometryCode, std::string& fragmentCode)
{
    clearUniforms();
    shader.compileAndLink(vertexCode,geometryCode,fragmentCode);
    mapAllUniforms();
}

void Renderer::render(Grid& grid)
{
    shader.use();
    grid.bindVao();
    shader.setUniform("ortho",projection::orthogonal);
    shader.setUniform("t",grid.getT());
    shader.setUniform("mag",(float)grid.getMagnitude());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES,0,grid.noOfVertices());
    glDisableVertexAttribArray(0);
    grid.unbindVao();
    shader.unuse();

}

void Renderer::mapAllUniforms()
{
    shader.mapUniform("ortho");
    shader.mapUniform("t");
    shader.mapUniform("mag");
}

void Renderer::clearUniforms()
{
    shader.clearUniforms();
}
