/*
    Project Corrode Simulation Engine
    entity.hpp - Root abstract class for entities in the simulation env
*/
#pragma once

// Common
#include <common/transform.hpp>
// Sim
#include <world.hpp>

namespace Simulation{
    class World;

    class Entity{
    protected:
    public:
        Entity();

        Transform transform;

        virtual void tick(World* world) = 0;

        virtual ~Entity() = default;
    };
}