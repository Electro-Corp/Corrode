/*
    Project Corrode Simulation Engine
    eat_behavior.cpp - Roam around 
*/

#include <behaviours/eat_behavior.hpp>
// Basic entity
#include <entities/basic_entity.hpp>

namespace Simulation{

EatBehavior::EatBehavior(){

}

// Execute this behavior
void EatBehavior::execute(Entity* entity, World* world){
    entity->stats[HUNGER] -= entity->statMods[HUNGER] * 2;
    world->terrain->cellAt(entity->transform.getPosition().x, entity->transform.getPosition().z).vegetation.amount -= entity->statMods[HUNGER] * 1.2 * world->delta;

    if(entity->stats[HUNGER] > entity->statLimits[HUNGER]){
        priority = 10.0;
        entity->stop();
    }else{
        priority = 1.0;
    }
}

} // SIMUlATION