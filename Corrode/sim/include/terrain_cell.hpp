/*
    Project Corrode Simulation Engine
    terrain_cell.hpp - Contains structs related to data of sections of terrain
*/
#pragma once

#include <array>

struct Soil {
    float fertility = 0.0f;
};

struct Vegitation {
    float amount = 0.0f;
};

struct Water {
    float surfaceAmount = 0.0f;
    float groundwaterAmount = 0.0f;
    bool belowWater = false;
};

struct TerrainCell {
    Soil soil; 
    Vegitation vegitation;
    Water water;

    float elevation = 0.0f;
    std::array<float, 4> cornerHeights{};
};
