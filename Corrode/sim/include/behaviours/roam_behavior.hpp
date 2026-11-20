/*
    Project Corrode Simulation Engine
    roam_behavior.hpp - Have an entity just walk around
*/
#pragma once

#include <behavior.hpp>

namespace Simulation{
    class RoamBehavior : public Behavior {
    public:
        RoamBehavior();

        // Execute this behavior
        void execute(Entity* entity, World* world) override;
    };
}
