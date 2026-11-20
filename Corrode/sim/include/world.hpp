/*
    Project Corrode Simulation Engine
    world.hpp - Class that holds entities and terrain
*/
#pragma once

// C++ STD
#include <memory>
// Sim includes
#include <entity.hpp>
#include <terrain.hpp>

namespace Simulation {
    class Entity;

    class World {
    private:
        // List of entities
        std::vector<std::shared_ptr<Entity>> entities;
    public:
        World();

        // Add entity
        void addEntity(std::shared_ptr<Entity> e){ entities.push_back(e); }

        void tick(double delta);

        // Terrain
        std::shared_ptr<Terrain> terrain;
        // Delta time
        double delta;
    };
}