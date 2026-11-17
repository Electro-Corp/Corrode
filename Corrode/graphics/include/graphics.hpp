/*
    Project Corrode Graphics Engine (PCGE)
    graphics.hpp - Header file for the graphics engine
*/
#pragma once
// Third Party Includes
#include <glad.h> 
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
// Corrode
#include <common/log.hpp>
// Graphics
#include <scene.hpp>
#include <camera.hpp>
#include <light.hpp>
#include <shader.hpp>

namespace Rendering{
    struct Color{
        float r, g, b, a;
    };

    struct EngineInitOptions{
        char name[32]; // Window title
        int h, w; // Window height and width
        Color clearColor; // OpenGL clear color
        unsigned int shadowSize = 1024, mapSize = 256;
    };

    class GraphicsEngine{
    private:
        // Window stuff
        int windowHeight = 600, windowWidth = 800;
        GLFWwindow* window;
        // GL
        Color clearColor;
        
        // Shadow stuff
        unsigned int depthMapFB, depthMap;
        unsigned int shadowWidth, shadowHeight;
        float shadowNear = 0.5f, shadowFar = 2048.f;
        std::unique_ptr<ShaderProgram> depthShader;
        glm::mat4 lightProjection, lightView, lightSpaceMatrix;
        unsigned int mapSize;

        // Configure shadow shader/matrices
        void configureShadows(Camera& cam, Light light);

        // Window resize callback
        static void windowResizedCallback(GLFWwindow* window, int w, int h){ 
            auto renderer = reinterpret_cast<GraphicsEngine*>(glfwGetWindowUserPointer(window));
            renderer->setDim(w, h);
            glViewport(0, 0, w, h); 
        }
    public:
        // Create graphics engine with the specfied options
        GraphicsEngine(EngineInitOptions initOptions);

        // Tick graphics system
        int tick(Scene scene, Rendering::Camera& cam, Light sun);

        // Getters/setters
        GLFWwindow* getWindow() const;
        void setDim(int w, int h){ this->windowWidth = w; this->windowHeight = h; }

        // Vars
        double lastFrameTime = 0.0;

    };
}
