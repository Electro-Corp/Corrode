/*
    Project Corrode Simulation Engine
    roam_behavior.cpp - Roam around 
*/

#include <behaviours/roam_behavior.hpp>

#include <common/log.hpp>

namespace Simulation{

RoamBehavior::RoamBehavior(){

}

// Execute this behavior
void RoamBehavior::execute(Entity* entity, World* world){
    double dX = ((rand() / 32767.0) * 2.0 - 1.0);
    double dY = ((rand() / 32767.0) * 2.0 - 1.0);

    entity->move(dX * world->delta, dY * world->delta, world);
}

} // SIMUlATION