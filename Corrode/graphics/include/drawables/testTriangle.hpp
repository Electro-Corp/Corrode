/*
    Project Corrode Graphics Engine (PCGE)
    testTriangle.hpp - Drawable triangle (for testing OpenGL)
*/
#ifndef DRAWABLE_TEST_TRIANGLE
#define DRAWABLE_TEST_TRIANGLE
// C++ STD
#include <memory>
// Graphics Engine includes
#include <drawable.hpp>
#include <camera.hpp>
#include <shader.hpp>

namespace Drawable{
    // All drawables extend from Rendering::Drawable 
    class TestTriangle : public Rendering::Drawable{
    private:
        // Vertices
        float vertices[3][3];
        // OpenGL Vertex buffers (TODO: probabbly make a common class for this)
        unsigned int VAO, VBO;
        // Shaders
        std::unique_ptr<Rendering::ShaderProgram> shaderProgram;
    public:
        TestTriangle();

        void draw(const Rendering::Camera& cam) override;
    };

}

#endif