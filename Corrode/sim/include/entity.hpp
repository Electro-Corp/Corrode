/*
    Project Corrode Simulation Engine
    entity.hpp - Root abstract class for entities in the simulation env
*/
#pragma once

#include <common/transform.hpp>

namespace Simulation{
    class Entity{
    protected:
        Transform transform;
    public:
        Entity();
    };
}