/*
    Project Corrode
    object.hpp - Extends Object to preform tests
*/
// Core
#include <core/objects/terrain_object.hpp>
// Graphics
#include <graphics/include/drawables/mesh.hpp>
// Terrain/simulation
#include <sim/include/generators/flat_generator.hpp>
// glad
#include <glad.h>

TerrainObject::TerrainObject(){
    this->terrain = std::make_unique<Simulation::Terrain>(257, 257);
    Simulation::FlatTerrainGenerator flatTerrainGenerator(100.0f);
    flatTerrainGenerator.generate(*(this->terrain), {20323120});

    //
    // What follows is a lot of testing stuff
    // that should be redone 
    //

    int width = terrain->width();
    int depth = terrain->depth();

    // Initialize texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    textures.emplace_back(textureID, std::string("texture_diffuse"), std::string("null"));
    // Temporary texture storage
    unsigned char* textureData = new unsigned char[width * depth * 3];

    // Generate vertices (and texture) based on terrain gen
    for(int i = 0; i < width; i++){
        for(int j = 0; j < depth; j++){
            int h = terrain->heightAt(i, j);
            // Generate vertice
            vertices.emplace_back(
                glm::vec3(i * SCALE_FACTOR, h * SCALE_FACTOR, j * SCALE_FACTOR),
                glm::vec2((float) i / (float) width, (float) j / (float)depth)
            );
            // Generate texture pixel
            unsigned int location = (i + (j * width)) * 3;
            textureData[location] = i;
            textureData[location + 1] = j;
            textureData[location + 2] = h;
        }
    }

    // Copy data to texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, depth, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //delete textureData;
    
    // Generate indices
    // Adapted from https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/indexbuffers/Tutorial%208%20-%20Index%20Buffers.pdf
    for(int i = 0; i < width - 1; i++){
        for(int j = 0; j < depth - 1; j++){
            // "Patch"
            int a = (i * width) + j;
            int b = ((i + 1) * width) + j;
            int c = ((i + 1) * width) + (j + 1);
            int d = (i * width) + (j + 1);

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