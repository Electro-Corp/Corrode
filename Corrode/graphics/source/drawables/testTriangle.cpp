/*
    Project Corrode Graphics Engine (PCGE)
    testTriangle.cpp - Drawable triangle (for testing OpenGL)
*/
#include <glad.h>
// Root
#include <drawables/testTriangle.hpp>

namespace Drawable{

TestTriangle::TestTriangle(){
    // Assign vertices (ugly)
    vertices[0][0] = -0.5f;
    vertices[0][1] = -0.5f;
    vertices[0][2] =  0.0f;
    vertices[1][0] =  0.5f;
    vertices[1][1] = -0.5f;
    vertices[1][2] =  0.0f;
    vertices[2][0] =  0.0f;
    vertices[2][1] =  0.5f;
    vertices[2][2] =  0.0f;
    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // Create VBO
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // GL_STATIC_DRAW means vertex data is set once and used a bunch (for things that change, probabbly use GL_DYNAMIC_DRAW)
    // Tell GL how to interpret vertex data, because our vertex data looks like:
    //    V1         V2       V3
    // [x][y][z] [x][y][z] [x][y][z]
    // ---(12)-> ---(12)-> ---(12)->
    //                  index, size                      stride
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Create shaders
    Rendering::Shader* vertexShader = new Rendering::Shader("../assets/shaders/test.vert", Rendering::ShaderType::VERTEX);
    Rendering::Shader* fragShader = new Rendering::Shader("../assets/shaders/test.frag", Rendering::ShaderType::FRAGMENT);
    // Compile them
    vertexShader->compileShader();
    fragShader->compileShader();
    // Create shader program (which will delete the previous shaders!)
    this->shaderProgram = std::make_unique<Rendering::ShaderProgram>(vertexShader, fragShader);
} 

void TestTriangle::draw(const Rendering::Camera& cam){
    glUseProgram(this->shaderProgram->getShaderProgram());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // DRAWABLE