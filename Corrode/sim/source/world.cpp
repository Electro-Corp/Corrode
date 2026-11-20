/*
    Project Corrode Simulation Engine
    world.cpp - Holds entities and terrain
*/
#include <world.hpp>

namespace Simulation {

World::World(){

}

void World::tick(double delta){
    this->delta = delta;
    // Tick all entities
    for(auto& e : entities){
        e->tick(this);
    }
}

} // SIMULATION