/*
    Project Corrode Simulation Engine
    terrain_cell.hpp - Contains structs related to data of sections of terrain
*/
#pragma once

struct Soil {
    float fertility;
};

struct Water {
    float surfaceAmount;
    float groundwaterAmount;
};

struct TerrainCell {
    Soil soil; 
    Water water;
};
