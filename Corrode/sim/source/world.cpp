/*
    Project Corrode Simulation Engine
    world.cpp - Holds entities and terrain
*/
#include <world.hpp>

namespace Simulation {

World::World(){

}

void World::tick(){
    for(auto& e : entities){
        e->tick(this);
    }
}

} // SIMULATION