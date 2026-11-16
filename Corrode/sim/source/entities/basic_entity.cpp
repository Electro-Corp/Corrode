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
    // Bound it
    if(this->transform.getPosition().x + xOff > world->terrain->width()) xOff = 0.0;
    if(this->transform.getPosition().x + xOff < 0) xOff = 0.0;
    if(this->transform.getPosition().z + zOff > world->terrain->depth()) zOff = 0.0;
    if(this->transform.getPosition().z + zOff < 0) zOff = 0.0;
    // Snap to the ground
    this->transform.setPosition(glm::vec3(this->transform.getPosition().x + xOff, world->terrain->heightAt(this->transform.getPosition().x, this->transform.getPosition().z) + 20, this->transform.getPosition().z + zOff));
}

} // SIMULATION