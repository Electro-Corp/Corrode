/*
    Project Corrode
    shader.hpp - Store a shader and its related functions
*/
#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace Rendering{
    enum ShaderType{
        VERTEX = 0x8B31, 
        FRAGMENT = 0x8B30
    };

    class Shader{
    private:
        // Raw shader data
        std::string shaderSource;
        // Type of shader
        ShaderType shaderType;
        // Internal OpenGL shader
        unsigned int shaderNum;
    public:
        Shader(std::string filePath, ShaderType shaderType);

        void compileShader();

        const char* getShaderSource() { return shaderSource.c_str(); }
    };
} // Rendering