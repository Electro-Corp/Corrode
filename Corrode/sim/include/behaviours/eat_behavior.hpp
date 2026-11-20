/*
    Project Corrode Simulation Engine
    eat_behavior.hpp - Have an entity just walk around
*/
#pragma once

#include <behavior.hpp>

namespace Simulation{
    class EatBehavior : public Behavior {
    public:
        EatBehavior();

        // Execute this behavior
        void execute(Entity* entity, World* world) override;
    };
}
