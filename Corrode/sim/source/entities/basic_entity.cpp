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
    statMods[HUNGER] = ((rand() % 10) * rand() % 10);
    statMods[THIRST] = 0.00; // Don't do thirst yet
    // Setup limits
    statLimits[HUNGER] = 45 + (rand() % 10);
    statLimits[THIRST] = 35 + (rand() % 10);
    // Setup stats
    stats[HUNGER] = 0.0;
    stats[THIRST] = 0.0;
    stats[SEXUAL] = 0.0;
    stats[FEAR] = 0.0;
    // One time things
    this->dead = false;
    this->outOfWater = false;
    // Add all the behaviors
    behaviors.push_back(&roam);
    behaviors.push_back(&findFood);
    behaviors.push_back(&eat);
}

void BasicEntity::tick(World* world){
    if(!dead){
        // Update stats
        updateStats(world);
        // Find the highest weighted thing
        double hBehaviorW = 0.0; // Save the highest weight so we dont need to make unnnessary calls to vector[id]
        int id = 0; 
        for(int i = 0; i < behaviors.size(); i++){
            if((behaviors[i]->weight * behaviors[i]->priority) > hBehaviorW){
                hBehaviorW = behaviors[i]->weight * behaviors[i]->priority;
                id = i;
            }
        }
        // Exeucte the highest weighted action
        behaviors[id]->execute(this, world);
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
    xOff += dx;
    zOff += dy;
    // Calculate movement    
    const float nextX = this->transform.getPosition().x + static_cast<float>(xOff);
    const float nextZ = this->transform.getPosition().z + static_cast<float>(zOff);
    std::size_t cellX = 0;
    std::size_t cellZ = 0;

    // Is it a valid cell
    if(!world->terrain->cellCoordinatesAt(nextX, nextZ, cellX, cellZ)) {
        zOff *= -1;
        xOff *= -1;
        return;
    }

    // Is it water?
    if((world->terrain->belowWaterAt(nextX, nextZ))){
        // Let jits escape the water
        if(outOfWater) {
            xOff *= -1;
            zOff *= -1;
            return;
        }
    }else{
        outOfWater = true;
    }

    // Move
    // Snap to the ground
    this->transform.setPosition(glm::vec3(
        nextX,
        world->terrain->surfaceHeightAt(cellX, cellZ) + 2.0,
        nextZ
    ));
}

void BasicEntity::stop(){
    zOff = 0;
    xOff = 0;
}

void BasicEntity::updateStats(World* world){
    double movementPenalty = ((((xOff * xOff) + (zOff * zOff)) * 500) + 1);
    // Update all stats
    stats[HUNGER] += statMods[HUNGER] * world->delta * movementPenalty * 10;
    stats[THIRST] += statMods[THIRST] * world->delta;
    stats[HAPPINESS] = 100 - ((stats[HUNGER] / 2) + (stats[THIRST] / 2));

    // Check if we're dead
    if(stats[HUNGER] > 100.0 || stats[THIRST] > 100.0){
        this->dead = true;
    }

    // Update weights
    roam.weight = (stats[HAPPINESS] + stats[SEXUAL]) / (stats[FEAR] + 1);
    findFood.weight = stats[HUNGER] / stats[HAPPINESS];
    eat.weight = (world->terrain->cellAt(transform.getPosition().x, transform.getPosition().z).vegetation.amount * 5) + stats[HUNGER];

    // LOG("BasicEntity::updateStats", std::string{
    //     "roam[" + std::to_string(roam.weight) + "], "
    //     + "findFood[" + std::to_string(findFood.weight) + "], "
    //     + "eat[" + std::to_string(eat.weight) + "]"
    // });
}

} // SIMULATION
