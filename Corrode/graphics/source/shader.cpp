/*
    Project Corrode
    shader.cpp - Implement shader and its related functions
*/
#include <shader.hpp>
#include <util/log.hpp>
// glad for OpenGL 
#include <glad.h>

namespace Rendering{

Shader::Shader(std::string shaderPath, ShaderType shaderType){
    std::ifstream fileStream(shaderPath, std::ios::ate);
    if(!fileStream.is_open()){
        Util::Log("Shader::Shader", std::string{"Failed to open " + shaderPath + "!\n"});
        // TODO: Add crash handler or sum
        exit(-1);
    }
    // Get size of file
    std::streamsize size = fileStream.tellg();
    this->shaderSource.resize(size);
    // Read file
    fileStream.read(&this->shaderSource[0], size);
    // Set shader type
    this->shaderType = shaderType;
}

void Shader::compileShader(){
    this->shaderNum = glCreateShader(shaderType);
    // Compile source
    const char* src = this->getShaderSource(); // source
    glShaderSource(this->shaderNum, 1, &src, NULL);
    glCompileShader(this->shaderNum);
    // Check if it compiled
    int success;
    char log[512];
    glGetShaderiv(this->shaderNum, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(this->shaderNum, 512, NULL, log);
        Util::Log("Shader::compileShader", std::string{"Shader compilation failed! Log: " + std::string(log) + "\n"});
        // TODO: Add crash handler or sum
        exit(-1);
    }
}

Shader::~Shader(){
    glDeleteShader(this->shaderNum);
}

ShaderProgram::ShaderProgram(Shader* vertex, Shader* frag){
    this->shaderProgram = glCreateProgram();
    // Attach the shaders to the program
    glAttachShader(shaderProgram, vertex->getShader());
    glAttachShader(shaderProgram, frag->getShader());
    // Link the program
    glLinkProgram(shaderProgram);
    // Check for errors
    int success;
    char log[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        Util::Log("ShaderProgram::ShaderProgram", std::string{"Shader linking failed! Log: " + std::string(log) + "\n"});
        // TODO: Add crash handler or sum
        exit(-1);
    }
    // Delete the original Shaders 
    delete(vertex);
    delete(frag);
}

} // Rendering