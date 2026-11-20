/*
    Project Corrode Simulation Engine
    roam_behavior.cpp - Roam around 
*/

#include <behaviours/roam_behavior.hpp>

namespace Simulation{

RoamBehavior::RoamBehavior(){

}

// Execute this behavior
void RoamBehavior::execute(Entity* entity, World* world){
    double dX = ((rand() / 32767.0) * 2.0 - 1.0) / 100;
    double dY = ((rand() / 32767.0) * 2.0 - 1.0) / 100;

    entity->move(dX, dY, world);
}

} // SIMUlATION