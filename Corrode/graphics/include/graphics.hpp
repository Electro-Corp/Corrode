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
// Graphics
#include <scene.hpp>

namespace Rendering{
    struct Color{
        float r, g, b, a;
    };

    struct EngineInitOptions{
        char name[32]; // Window title
        int h, w; // Window height and width
        Color clearColor; // OpenGL clear color
    };

    class GraphicsEngine{
    private:
        // Window stuff
        int windowHeight = 600, windowWidth = 800;
        GLFWwindow* window;
        // GL
        Color clearColor;

        // Window resize callback
        static void windowResizedCallback(GLFWwindow* window, int w, int h){ glViewport(0, 0, w, h); }
    public:
        // Create graphics engine with the specfied options
        GraphicsEngine(EngineInitOptions initOptions);

        // Tick graphics system
        int tick(Scene scene);
    };
}