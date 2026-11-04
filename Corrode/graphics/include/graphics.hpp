/*
    Project Corrode Graphics Engine (PCGE)
    graphics.hpp - Header file for the graphics engine
*/
#pragma once

#include <GLFW/glfw3.h>

namespace Rendering{
    class GraphicsEngine{
    private:
        // Window stuff
        int windowHeight = 600, windowWidth = 800;
        GLFWwindow* window;
    public:
        GraphicsEngine();

        // Tick graphics system
        int tick();
    };
}