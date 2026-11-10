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
