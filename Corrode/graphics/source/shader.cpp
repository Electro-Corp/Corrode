/*
    Project Corrode
    shader.cpp - Implement shader and its related functions
*/
#include <shader.hpp>
#include <util/log.hpp>

namespace Rendering{

Shader::Shader(std::string shaderPath){
    std::ifstream fileStream(shaderPath);
    if(!fileStream.is_open()){
        Util::Log("Shader::Shader", std::string{"Failed to open " + shaderPath + "!\n"});
        // TODO: Add crash handler or sum
        exit(-1);
    }
    // Read file
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    this->shaderSource = buffer.str();
}

} // Rendering