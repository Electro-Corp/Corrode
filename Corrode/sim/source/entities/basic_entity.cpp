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
    this->modHunger = 0.05;
    this->modThirst = 0.00; // Don't do thirst yet
    // Setup stats
    this->hunger = 0.0;
    this->thirst = 0.0;
    // Inital goal
    this->goal = IDLE;
    // Dead
    this->dead = false;
}

void BasicEntity::tick(World* world){
    // Update stats
    updateStats(); // Keep out of if !dead because i use the hunger value as a param for sin once its dead
    if(!dead){
        // Debug log stats
        //Util::Log("BasicEntity::tick", std::string{"Hunger: " + std::to_string(hunger) + " | Thirst: " + std::to_string(thirst) + " | Action: " + std::to_string(goal)});
        
        // What goal is he pursing
        switch(goal){
            case IDLE:
                // Chance of staying idle or starting to move
                if(rand() / 32767.0 > 0.9) goal = ROAM;
                break;
            case ROAM:
                xOff += ((rand() / 32767.0) * 2.0 - 1.0) / 100;
                zOff += ((rand() / 32767.0)* 2.0 - 1.0) / 100;
                break;   
            case FIND_FOOD:
                // todo: function in terrain that finds closest cell with desired parameter (fertility, etc)
                goal = GO_TO_FOOD;
                break;
            case GO_TO_FOOD:
                xOff += ((rand() / 32767.0) * 2.0 - 1.0) / 100;
                zOff += ((rand() / 32767.0)* 2.0 - 1.0) / 100;
                if(world->terrain->cellAt(this->transform.getPosition().x + static_cast<float>(xOff), this->transform.getPosition().z + static_cast<float>(zOff)).vegetation.amount > 0.01){
                    goal = EAT;
                }
                break;
            case EAT:
                xOff = 0;
                zOff = 0;
                this->hunger -= this->modHunger * 2;
                world->terrain->cellAt(this->transform.getPosition().x + static_cast<float>(xOff), this->transform.getPosition().z + static_cast<float>(zOff)).vegetation.amount -= this->modHunger * 2;
                // Are we done?
                if(this->hunger < 10.0) goal = IDLE;
                break;
            default:
                break;
        }


        // Move our jit    
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
    }else{
        // Bob up and down so we know you dead
        this->transform.setPosition(glm::vec3(
            this->transform.getPosition().x,
            this->transform.getPosition().y + 0.3 * sin(this->hunger),
            this->transform.getPosition().z
        ));
    }
}

void BasicEntity::updateStats(){
    // Update all stats
    this->hunger += this->modHunger;
    this->thirst += this->modThirst;


    // Check if we're dead
    if(hunger > 100.0 || thirst > 100.0){
        this->dead = true;
    }

    // Check if goal needs to be updated
    if(goal < FIND_FOOD || goal > FIND_WATER){
        if(thirst > 50.0) goal = FIND_WATER;
        if(hunger > 50.0) goal = FIND_FOOD;
    }
}

} // SIMULATION
