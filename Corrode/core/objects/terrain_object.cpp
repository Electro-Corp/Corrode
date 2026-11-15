/*
    Project Corrode
    object.hpp - Extends Object to preform tests
*/
// Core
#include <core/objects/terrain_object.hpp>
#include <core/objects/terrain_debug_view.hpp>
// Common
#include <common/rgb.hpp>
// Graphics
#include <graphics/include/drawables/mesh.hpp>
// Terrain/simulation
#include <sim/include/generators/flat_generator.hpp>
#include <sim/include/generators/noise_generator.hpp>
#include <sim/include/passes/water_level_pass.hpp>
// glad
#include <glad.h>
// C++ STD
#include <vector>

TerrainObject::TerrainObject(){
    this->terrain = std::make_unique<Simulation::Terrain>(1024, 1024);
    Simulation::FlatTerrainGenerator flatTerrainGenerator(100.0f);
    Simulation::NoiseTerrainGenerator noiseTerrainGenerator;
    // constexpr TerrainDebugView debugView = TerrainDebugView::WaterClassification;
    // constexpr TerrainDebugView debugView = TerrainDebugView::CoordinateGrid;
    constexpr TerrainDebugView debugView = TerrainDebugView::HeightGradient;
    // constexpr TerrainDebugView debugView = TerrainDebugView::ElevationBands;
    
    Simulation::TerrainGenerationSettings terrainSettings{
        4323122924, // Scale 
        2.0f,       // Frequency
        6,          // Octaves
        160.0f,      // Scale
        0.0f        // Water Height
    };

    noiseTerrainGenerator.generate(*(this->terrain), terrainSettings);

    Simulation::WaterLevelPass waterLevelPass;
    waterLevelPass.apply(*(this->terrain), terrainSettings);

    //
    // What follows is a lot of testing stuff
    // that should be redone 
    //

    std::size_t width = terrain->width();
    std::size_t depth = terrain->depth();
    float minimumElevation = terrain->heightAt(0, 0);
    float maximumElevation = minimumElevation;
    for(std::size_t z = 0; z < depth; z++) {
        for(std::size_t x = 0; x < width; x++) {
            const float elevation = terrain->heightAt(x, z);
            if(elevation < minimumElevation) minimumElevation = elevation;
            if(elevation > maximumElevation) maximumElevation = elevation;
        }
    }

    // Initialize texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    textures.emplace_back(textureID, std::string("texture_diffuse"), std::string("null"));
    // Temporary texture storage
    std::vector<unsigned char> textureData(width * depth * 3);

    // Generate vertices (and texture) based on terrain gen
    for(std::size_t z = 0; z < depth; z++){
        for(std::size_t x = 0; x < width; x++){
            float height = terrain->heightAt(x, z);
            RGB color = terrainDebugColor(
                debugView,
                *terrain,
                x,
                z,
                minimumElevation,
                maximumElevation,
                terrainSettings.water_level
            );

            // Generate vertice
            vertices.emplace_back(
                glm::vec3(x * terrain->cellSize(), height, z * terrain->cellSize()),
                glm::vec2((float) x / (float) width, (float) z / (float)depth),
                glm::vec3(0.0, 0.0, 0.0) // dummy normal for until we get indices
            );
            // Generate texture pixel
            unsigned int location = (x + (z * width)) * 3;
            textureData[location] = static_cast<unsigned char>(color.r);
            textureData[location + 1] = static_cast<unsigned char>(color.g);
            textureData[location + 2] = static_cast<unsigned char>(color.b);
        }
    }

    // Copy data to texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, depth, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate indices
    // Adapted from https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/indexbuffers/Tutorial%208%20-%20Index%20Buffers.pdf
    for(std::size_t z = 0; z < depth - 1; z++){
        for(std::size_t x = 0; x < width - 1; x++){
            // "Patch"
            std::uint32_t a = (z * width) + x;
            std::uint32_t b = (z * width) + (x + 1);
            std::uint32_t c = ((z + 1) * width) + (x + 1);
            std::uint32_t d = ((z + 1) * width) + x;

            ind.push_back(c);
            ind.push_back(b);
            ind.push_back(a);

            ind.push_back(a);
            ind.push_back(d);
            ind.push_back(c);
        }
    }

    // Shader
    Rendering::Shader* vertex = new Rendering::Shader("../assets/shaders/terrain.vert", Rendering::VERTEX);
    Rendering::Shader* fragment = new Rendering::Shader("../assets/shaders/terrain.frag", Rendering::FRAGMENT);
    this->shaderProgram = std::make_shared<Rendering::ShaderProgram>(vertex, fragment);

    // Final drawable
    this->drawable = std::make_shared<Drawable::Mesh>(vertices, ind, textures, shaderProgram);
}

void TerrainObject::tick(){
    
}
