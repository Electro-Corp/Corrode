/*
    Project Corrode Simulation Engine
    find_food_behavior.hpp - Find food
*/
#pragma once

#include <behavior.hpp>

namespace Simulation{
    class FindFoodBehavior : public Behavior {
    public:
        FindFoodBehavior();

        // Execute this behavior
        void execute(Entity* entity, World* world) override;
    };
}
