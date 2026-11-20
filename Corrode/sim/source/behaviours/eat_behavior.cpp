/*
    Project Corrode Simulation Engine
    eat_behavior.cpp - Roam around 
*/

#include <behaviours/eat_behavior.hpp>
// Basic entity
#include <basic_entity.hpp>

namespace Simulation{

EatBehavior::EatBehavior(){

}

// Execute this behavior
void EatBehavior::execute(Entity* entity, World* world){
    entity->stats[HUNGER] -= entity->statMods[HUNGER] * 2;
    world->terrain->cellAt(entity->transform.getPosition().x, entity->transform.getPosition().z).vegetation.amount -= entity->statMods[HUNGER] * 2;;
}

} // SIMUlATION