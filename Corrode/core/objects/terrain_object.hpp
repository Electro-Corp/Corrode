/*
    Project Corrode
    terrain_object.hpp - Extends Object to generate and render some terrain
*/
// Core
#include <core/object.hpp>
#include <core/objects/terrain_debug_view.hpp>
// Graphics
#include <graphics/include/drawables/mesh.hpp>
#include <graphics/include/shader.hpp>
// Terrain
#include <sim/include/terrain.hpp>
#include <sim/include/terrain_generator.hpp>
// C++
#include <memory>
#include <cstdint>

class TerrainObject : public Object {
private:
    std::shared_ptr<Simulation::Terrain> terrain;
    // Shaders
    std::shared_ptr<Rendering::ShaderProgram> shaderProgram;
    // Textures
    std::vector<Drawable::Texture> textures;
    // Vertices, indices, and normals
    std::vector<Drawable::Vertex> vertices;
    std::vector<std::uint32_t> ind;
    TerrainDebugView activeDebugView_ = TerrainDebugView::RawPerlinNoise;
    Simulation::TerrainGenerationSettings terrainSettings_;
    unsigned int diffuseTextureID_ = 0;
    float minimumElevation_ = 0.0f;
    float maximumElevation_ = 0.0f;
    float rawMinimum_ = 0.0f;
    float rawMaximum_ = 0.0f;
    std::vector<float> rawSamples_;
    bool previousLeftPressed_ = false;
    bool previousRightPressed_ = false;

    void updateDebugTexture();
    void updateDebugModeUniforms();
public:
    TerrainObject(unsigned int size);

    void tick() override;
    void tick(GLFWwindow* window);

    // Getters/Setters
    std::shared_ptr<Simulation::Terrain> getTerrain() { return terrain; }
};
