#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    programID = glCreateProgram();

}


ShaderProgram::~ShaderProgram()
{}

void ShaderProgram::createShader(unsigned int& id, int shaderType, std::string& code)
{
    id = glCreateShader(shaderType);
    const char* cCode = code.c_str();
    glShaderSource(id,1,&cCode,NULL);
    glCompileShader(id);

    int success;
    char infoLog[512];

    glGetShaderiv(id,GL_COMPILE_STATUS,&success);

    if(!success)
    {
        glGetShaderInfoLog(id,512,NULL,infoLog);
        std::cerr << infoLog << std::endl;
    }
}

void ShaderProgram::compileAndLink(std::string& vertexCode, std::string& fragmentCode)
{
    glLinkProgram(0);

    createShader(vertexID,GL_VERTEX_SHADER,vertexCode);
    createShader(fragmentID,GL_FRAGMENT_SHADER,fragmentCode);

    glAttachShader(programID,vertexID);
    glAttachShader(programID,fragmentID);

    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

void ShaderProgram::compileAndLink(std::string& vertexCode, std::string& geometryCode, std::string& fragmentCode)
{
    glLinkProgram(0);

    createShader(vertexID,GL_VERTEX_SHADER,vertexCode);
    createShader(geometryID,GL_GEOMETRY_SHADER,geometryCode);
    createShader(fragmentID,GL_FRAGMENT_SHADER,fragmentCode);

    glAttachShader(programID,vertexID);
    glAttachShader(programID,geometryID);
    glAttachShader(programID,fragmentID);

    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(geometryID);
    glDeleteShader(fragmentID);
}

void ShaderProgram::mapUniform(std::string uniformName)
{
    const char* cUniformName = uniformName.c_str();
    int uniformLoc = glGetUniformLocation(programID, cUniformName);
    uniformMap.insert(std::pair<std::string,int>(uniformName,uniformLoc));
}


void ShaderProgram::setUniform(std::string uniformName, float* arr)
{
    int uniformLoc = uniformMap[uniformName];
    glUniformMatrix4fv(uniformLoc,1,false,arr);
}

void ShaderProgram::setUniform(std::string uniformName, float val)
{
    int uniformLoc = uniformMap[uniformName];
    glUniform1f(uniformLoc,val);
}

void ShaderProgram::clearUniforms()
{
    uniformMap.clear();
}

void ShaderProgram::use()
{
    glUseProgram(programID);
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}
