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
#include <cstdint>

#define SCALE_FACTOR 1

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
public:
    TerrainObject(unsigned int size);

    void tick() override;

    // Getters/Setters
    std::shared_ptr<Simulation::Terrain> getTerrain() { return terrain; }
};
