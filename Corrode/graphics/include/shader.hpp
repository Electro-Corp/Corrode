/*
    Project Corrode Graphics Engine (PCGE)
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
        // 
        bool compiled;
    public:
        // Create a shader object
        Shader(std::string filePath, ShaderType shaderType);
        // Compile the shader
        void compileShader();

        // Getters
        const char* getShaderSource() { return shaderSource.c_str(); }
        unsigned int getShader() { return shaderNum; }
        bool wasCompiled() { return compiled; }

        // Destroy
        ~Shader();
    };

    class ShaderProgram{
    private:
        // Shader Program id
        unsigned int shaderProgram;
    public:
        // Create and link a shader program (WARNING: Destroys the Shader object in the process!!)
        ShaderProgram(Shader* vertex, Shader* frag);
        
        // Setters for things within shaders
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

        // Getters
        unsigned int getShaderProgram(){ return shaderProgram; }
    };
} // Rendering