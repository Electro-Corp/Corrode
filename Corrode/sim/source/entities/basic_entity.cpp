/*
    Project Corrode Simulation Engine
    basic_entity.cpp - Basic implementation of the entity
*/
#include <entities/basic_entity.hpp>

#include <stdlib.h>

namespace Simulation {

BasicEntity::BasicEntity(){
    this->xOff = 0.0;
    this->zOff = 0.0;
}

void BasicEntity::tick(World* world){
    // Move our jit
    xOff += ((rand() / 32767.0) * 2.0 - 1.0) / 100;
    zOff += ((rand() / 32767.0)* 2.0 - 1.0) / 100;
    const float nextX = this->transform.getPosition().x + static_cast<float>(xOff);
    const float nextZ = this->transform.getPosition().z + static_cast<float>(zOff);
    std::size_t cellX = 0;
    std::size_t cellZ = 0;
    if(!world->terrain->cellCoordinatesAt(nextX, nextZ, cellX, cellZ) || world->terrain->belowWaterAt(nextX, nextZ)) {
        xOff *= -1;
        zOff *= -1;
        return;
    }

    // Snap to the ground
    this->transform.setPosition(glm::vec3(
        nextX,
        world->terrain->surfaceHeightAt(cellX, cellZ) + 2.0f,
        nextZ
    ));
}

} // SIMULATION
