/*
    Project Corrode Simulation Engine
    basic_entity.cpp - Basic implementation of the entity
*/
#include <entities/basic_entity.hpp>

#include <stdlib.h>

namespace Simulation {

BasicEntity::BasicEntity(){
    // Setup offsets
    this->xOff = 0.0;
    this->zOff = 0.0;
    // Setup modfiers
    statMods[HUNGER] = 0.05 + (rand() % 5) / 5;
    statMods[THIRST] = 0.00; // Don't do thirst yet
    // Setup limits
    statLimits[HUNGER] = 45 + (rand() % 10);
    statLimits[THIRST] = 35 + (rand() % 10);
    // Setup stats
    stats[HUNGER] = 0.0;
    stats[THIRST] = 0.0;
    // One time things
    this->dead = false;
    this->outOfWater = false;
}

void BasicEntity::tick(World* world){
    // Update stats
    updateStats(); // Keep out of if !dead because i use the hunger value as a param for sin once its dead
    if(!dead){
        
    }else{
        // Bob up and down so we know you dead
        this->transform.setPosition(glm::vec3(
            this->transform.getPosition().x,
            this->transform.getPosition().y + 0.3 * sin(statMods[HUNGER]),
            this->transform.getPosition().z
        ));
    }
}

void BasicEntity::move(double dx, double dy, World* world){
    // Calculate movement    
    const float nextX = this->transform.getPosition().x + static_cast<float>(dx);
    const float nextZ = this->transform.getPosition().z + static_cast<float>(dy);
    std::size_t cellX = 0;
    std::size_t cellZ = 0;

    // Is it a valid cell
    if(!world->terrain->cellCoordinatesAt(nextX, nextZ, cellX, cellZ)) {
        return;
    }

    // Move
    // Snap to the ground
    this->transform.setPosition(glm::vec3(
        nextX,
        world->terrain->surfaceHeightAt(cellX, cellZ) + 2.0,
        nextZ
    ));
}

void BasicEntity::updateStats(){
    // Update all stats
    stats[HUNGER] += statMods[HUNGER];
    stats[THIRST] += statMods[THIRST];


    // Check if we're dead
    if(stats[HUNGER] > 100.0 || stats[THIRST] > 100.0){
        this->dead = true;
    }
}

} // SIMULATION
