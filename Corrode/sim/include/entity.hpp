/*
    Project Corrode Simulation Engine
    entity.hpp - Root abstract class for entities in the simulation env
*/
#pragma once

// Common
#include <common/transform.hpp>
// Sim
#include <world.hpp>

#define MAX_STATS 256

namespace Simulation{
    class World;

    class Entity{
    protected:
    public:
        Entity();

        // Transform
        Transform transform;
        // Stats
        double stats[MAX_STATS];
        double statMods[MAX_STATS];
        double statLimits[MAX_STATS];

        virtual void tick(World* world) = 0;

        // Universal functions to implement
        virtual void move(double dx, double dy, World* world) = 0;
        virtual void stop() = 0;

        virtual ~Entity() = default;
    };
}