/*
    Project Corrode Simulation Engine
    basic_entity.hpp - Basic implementation of the entity
*/
#pragma once

#include <entity.hpp>

namespace Simulation {
    class BasicEntity : public Entity {
    private:
        // To move our jit
        double xOff, zOff;
    public:
        BasicEntity();

        void tick(World* world) override;
    };
} // SIMULATION
