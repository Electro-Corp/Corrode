/*
    Project Corrode Graphics Engine (PCGE)
    graphics.cpp - Implementation for the graphics engine
*/
#include <graphics.hpp>

namespace Rendering{

// Graphics Engine Constructor
GraphicsEngine::GraphicsEngine(){
    // Init glfw
    glfwInit();
    // Set OpenGL params
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, "Corrode", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // Set user pointer
	glfwSetWindowUserPointer(window, this);
}

int GraphicsEngine::tick(){
    if(glfwWindowShouldClose(window)){
        return -1;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

} // Rendering
