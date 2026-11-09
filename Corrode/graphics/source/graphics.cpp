/*
    Project Corrode Graphics Engine (PCGE)
    graphics.cpp - Implementation for the graphics engine
*/
#include <graphics.hpp>

namespace Rendering{

// Graphics Engine Constructor
GraphicsEngine::GraphicsEngine(EngineInitOptions initOptions){
    // Load options
    windowHeight = initOptions.h;
    windowWidth = initOptions.w;
    clearColor = initOptions.clearColor;
    // Init glfw
    glfwInit();
    // Set OpenGL params
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, initOptions.name, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // Set user pointer
	glfwSetWindowUserPointer(window, this);

    // Init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        Util::Log("GraphicsEngine::GraphicsEngine", "Failed to load GLAD!\n");
        exit(-1);
    }

    // init viewport
    glViewport(0, 0, windowWidth, windowHeight);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Enable MSAA
    glEnable(GL_MULTISAMPLE);
    // Enable SRGB Gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);
    // Enable culling
    glEnable(GL_CULL_FACE);
    // Enable stencil testing 
    glEnable(GL_STENCIL_TEST);
    
    glfwSetFramebufferSizeCallback(window, windowResizedCallback);
}

int GraphicsEngine::tick(Scene scene, const Rendering::Camera& cam){
    if(glfwWindowShouldClose(window)){
        glfwTerminate();
        return -1;
    }

    // Clear color
    glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Render
    for(auto& gm : scene.getObjects()){
        gm->draw(cam);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

} // Rendering
