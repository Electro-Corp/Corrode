/*
    Project Corrode Simulation Engine
    basic_entity.hpp - Basic implementation of the entity
*/
#pragma once

// Sim
#include <entity.hpp>
// Behaviors
#include <behaviours/roam_behavior.hpp>
#include <behaviours/find_food_behavior.hpp>
#include <behaviours/eat_behavior.hpp>

// Common
#include <common/log.hpp>

namespace Simulation {
    enum Stats {
        HUNGER,
        THIRST,
        HAPPINESS,
        FEAR,
        ANGER,
        SEXUAL
    };

    class BasicEntity : public Entity {
    private:
        // To move our jit
        double xOff, zOff, targetX, targetZ;
        // One time variables
        bool dead, outOfWater;

        // His... desires!
        RoamBehavior roam;
        FindFoodBehavior findFood;
        EatBehavior eat;

        // Update stats
        void updateStats();
    public:
        BasicEntity();

        void tick(World* world) override;
        
        void move(double dx, double dy, World* world) override;
    };
} // SIMULATION
