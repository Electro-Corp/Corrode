/*
    Project Corrode Graphics Engine (PCGE)
    drawable.hpp - Class for things that can be drawn
*/
#pragma once

#include <common/transform.hpp>
#include <camera.hpp>
#include <shader.hpp>

namespace Rendering {
    class Drawable{
    private:
    public:
        Drawable();

        // Shaders
        std::shared_ptr<Rendering::ShaderProgram> shaderProgram;

        // Abstract function for child classes
        virtual void draw(const Rendering::Camera& cam) = 0;
    };
} // Rendering