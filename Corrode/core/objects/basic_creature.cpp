/*
    Project Corrode
    basic_creature.cpp - Extends Object to create a small little box that can do stuff
*/

#include <core/objects/basic_creature.hpp>

BasicCreature::BasicCreature(){
    // Generate vertices
    for(int i = 0; i < 216; i += 6){
        this->vertices.emplace_back(
            glm::vec3(rawVertexData[i], rawVertexData[i + 1], rawVertexData[i + 2]),
            glm::vec2(0, 0), // unnessary for cube.vert/frag
            glm::vec3(rawVertexData[i + 3], rawVertexData[i + 4], rawVertexData[i + 6])
        );
    }

    // Cube indices
    ind.insert(ind.end(), {0, 6, 7, 2, 3, 7}); // top
    ind.insert(ind.end(), {0, 4, 5, 0, 1, 5}); // bottom
    ind.insert(ind.end(), {0, 2, 6, 0, 4, 6}); // left
    ind.insert(ind.end(), {1, 3, 7, 1, 5, 7}); // right
    ind.insert(ind.end(), {0, 2, 3, 0, 1, 3}); // front
    ind.insert(ind.end(), {4, 6, 7, 4, 5, 7}); // back
    
    // Shader
    Rendering::Shader* vertex = new Rendering::Shader("../assets/shaders/cube.vert", Rendering::VERTEX);
    Rendering::Shader* fragment = new Rendering::Shader("../assets/shaders/cube.frag", Rendering::FRAGMENT);
    this->shaderProgram = std::make_shared<Rendering::ShaderProgram>(vertex, fragment);

    // Final drawable
    this->drawable = std::make_shared<Drawable::Mesh>(vertices, ind, textures, shaderProgram);    
}

void BasicCreature::tick(){
    this->drawable->transform = this->transform;
} 