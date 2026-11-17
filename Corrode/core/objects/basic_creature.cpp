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
            glm::vec3(rawVertexData[i + 3], rawVertexData[i + 4], rawVertexData[i + 5])
        );
    }

    // Cube indices
    for(int i = 0; i < 36; i++) ind.push_back(i);
    
    // Shader
    Rendering::Shader* vertex = new Rendering::Shader("../assets/shaders/cube.vert", Rendering::VERTEX);
    Rendering::Shader* fragment = new Rendering::Shader("../assets/shaders/cube.frag", Rendering::FRAGMENT);
    this->shaderProgram = std::make_shared<Rendering::ShaderProgram>(vertex, fragment);

    // Final drawable
    this->drawable = std::make_shared<Drawable::Mesh>(vertices, ind, textures, shaderProgram);    

    // Create entity
    this->entity = std::make_shared<Simulation::BasicEntity>();
}

BasicCreature::BasicCreature(glm::vec3 position) : BasicCreature() {
    this->transform.setPosition(position);
    this->entity->transform = this->transform;
}

void BasicCreature::tick(){
    this->transform.setPosition(entity->transform.getPosition());
    this->drawable->transform = this->transform;
} 