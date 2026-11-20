/*
    Project Corrode Simulation Engine
    behavior.hpp - Root abstract class for behaviours for entities to do
*/
#pragma once

#include <entity.hpp>
#include <terrain.hpp>

namespace Simulation{
    class Behavior{
    private:
    public:
        Behavior();

        virtual void execute(Entity* entity, World* terrain) = 0;

        double weight;
    };
}