/*
    Project Corrode Simulation Engine
    basic_entity.hpp - Basic implementation of the entity
*/
#pragma once

// Sim
#include <entity.hpp>
// Common
#include <common/log.hpp>

namespace Simulation {
    enum Goal {
        IDLE,
        ROAM,
        FIND_FOOD,
        GO_TO_FOOD,
        EAT,
        FIND_WATER
    };

    class BasicEntity : public Entity {
    private:
        // Stats
        double hunger, thirst;
        // Limits
        double hungerLimit, thirstLimit;
        // Stat modifiers
        double modHunger, modThirst;
        // To move our jit
        double xOff, zOff, targetX, targetZ;
        // His current goal
        Goal goal;
        // One time things
        bool dead, outOfWater;

        // Update stats
        void updateStats();
    public:
        BasicEntity();

        void tick(World* world) override;
    };
} // SIMULATION
