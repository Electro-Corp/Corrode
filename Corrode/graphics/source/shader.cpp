/*
    Project Corrode
    shader.cpp - Implement shader and its related functions
*/
#include <shader.hpp>
#include <util/log.hpp>

namespace Rendering{

Shader::Shader(std::string shaderPath){
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
}

} // Rendering