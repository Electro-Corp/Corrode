/*
    Project Corrode Graphics Engine (PCGE)
    graphics.hpp - Header file for the graphics engine
*/
#pragma once
// Third Party Includes
#include <glad.h> 
#include <GLFW/glfw3.h>
// Corrode
#include <util/log.hpp>

namespace Rendering{
    struct Color{
        float r, g, b, a;
    };

    struct EngineInitOptions{
        char name[32];
        int h, w;
        Color clearColor;
    };

    class GraphicsEngine{
    private:
        // Window stuff
        int windowHeight = 600, windowWidth = 800;
        GLFWwindow* window;
        // GL
        Color clearColor;
    public:
        GraphicsEngine(EngineInitOptions initOptions);

        // Tick graphics system
        int tick();
    };
}