/*
    Project Corrode Simulation Engine
    terrain_cell.hpp - Contains structs related to data of sections of terrain
*/
#pragma once

#include <array>

struct Soil {
    float fertility = 0.0f;
};

struct Vegetation {
    float amount = 0.0f;
};

struct Water {
    float surfaceAmount = 0.0f;
    float groundwaterAmount = 0.0f;
    bool belowWater = false;
};

struct TerrainCell {
    Soil soil; 
    Vegetation vegetation;
    Water water;

    float elevation = 0.0f;
    std::array<float, 4> cornerHeights{};
};
