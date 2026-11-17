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
    shadowHeight = shadowWidth = initOptions.shadowSize;
    mapSize = initOptions.mapSize;
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
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    // Enable MSAA
    glEnable(GL_MULTISAMPLE);
    // Enable SRGB Gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);
    // Enable culling (not for now... it messes up jit's rendering cuz the verts arent CCW)
    // glEnable(GL_CULL_FACE);
    // Enable stencil testing 
    glEnable(GL_STENCIL_TEST);
    
    // Shadows
    depthShader = std::make_unique<ShaderProgram>(
        new Shader("../assets/shaders/depth.vert", VERTEX),
        new Shader("../assets/shaders/depth.frag", FRAGMENT)
    );

    // Create depth map framebuffer
    glGenFramebuffers(1, &depthMapFB);

    // Create depth map
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);  
    float bColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bColor);

    // Bind it
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFB);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    glfwSetFramebufferSizeCallback(window, windowResizedCallback);
}

void GraphicsEngine::configureShadows(Camera& cam, Light light){
    lightProjection = glm::ortho(-(float)mapSize - 100, (float)mapSize + 100, -(float)mapSize - 100, (float)mapSize + 100, shadowNear, shadowFar);
    lightView = glm::lookAt(
        light.position,
        glm::normalize(glm::vec3(0.0) - light.position),
        glm::vec3(0.0, 1.0, 0.0)
    );
    lightSpaceMatrix = lightProjection * lightView;
    glUseProgram(depthShader->getShaderProgram());
    depthShader->setMat4("lSpaceMatrix", lightSpaceMatrix);
}

int GraphicsEngine::tick(Scene scene, Camera& cam, Light sun){
    if(glfwWindowShouldClose(window)){
        glfwTerminate();
        return -1;
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    const double currentTime = glfwGetTime();
    const float deltaTime = lastFrameTime > 0.0
        ? static_cast<float>(currentTime - lastFrameTime)
        : 0.0f;
    lastFrameTime = currentTime;
    if(cam.control) cam.control->handleInput(window, deltaTime);

    // Clear color
    glClearColor(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if(shadowWidth != 0){
        configureShadows(cam, sun);

        // Render for the depth map
        glViewport(0, 0, shadowWidth, shadowHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFB);
        glClear(GL_DEPTH_BUFFER_BIT);
        // Render with depth shader
        for(auto& gm : scene.getObjects()){
            gm->draw(cam, depthShader->getShaderProgram());
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Reset view port
        glViewport(0, 0, this->windowWidth, this->windowHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // Render for real
    for(auto& gm : scene.getObjects()){
        int shaderId = gm->shaderProgram->getShaderProgram();
        glUseProgram(shaderId);
        gm->shaderProgram->setVec3("viewPosition", const_cast<Rendering::Camera&>(cam).getPosition());
        gm->shaderProgram->setVec3("light.ambient", sun.ambient);
        gm->shaderProgram->setVec3("light.specular", sun.specular);
        gm->shaderProgram->setVec3("light.diffuse", sun.diffuse);
        gm->shaderProgram->setVec3("light.position", sun.position);

        // Add depth map to shader
        glActiveTexture(GL_TEXTURE0);
        int matLocation = glGetUniformLocation(shaderId, "depthMap");
        glUniform1i(matLocation, 0);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        gm->shaderProgram->setMat4("lSpaceMatrix", lightSpaceMatrix);

        gm->draw(cam);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    return 0;
}

GLFWwindow* GraphicsEngine::getWindow() const {
    return window;
}

} // Rendering
