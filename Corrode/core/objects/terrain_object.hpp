/*
    Project Corrode
    terrain_object.hpp - Extends Object to generate and render some terrain
*/
// Core
#include <core/object.hpp>
// Graphics
#include <graphics/include/drawables/mesh.hpp>
#include <graphics/include/shader.hpp>
// Terrain
#include <sim/include/terrain.hpp>
// C++
#include <memory>

class TerrainObject : public Object {
private:
    std::unique_ptr<Simulation::Terrain> terrain;
    // Shaders
    std::shared_ptr<Rendering::ShaderProgram> shaderProgram;
    // Textures
    std::vector<Drawable::Texture> textures;
    // Vertices and indices
    std::vector<Drawable::Vertex> vertices;
    std::vector<uint16_t> ind;
public:
    TerrainObject();

    void tick() override;
};