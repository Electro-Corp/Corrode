/*
    Project Corrode
    shader.hpp - Store a shader and its related functions
*/
#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace Rendering{
    class Shader{
    private:
        std::string shaderSource;
    public:
        Shader(std::string filePath);

        const char* getShaderSource() { return shaderSource.c_str(); }
    };
} // Rendering