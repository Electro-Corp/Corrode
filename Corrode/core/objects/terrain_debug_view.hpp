#pragma once

#include <cstddef>

#include <common/rgb.hpp>
#include <sim/include/terrain.hpp>

enum class TerrainDebugView {
    WaterClassification,
    ElevationBands,
    HeightGradient,
    CoordinateGrid,
    FertilityGradient,
    VegetationGradient,
    RawPerlinNoise,
    Count
};

RGB terrainDebugColor(
    TerrainDebugView view,
    const Simulation::Terrain& terrain,
    std::size_t x,
    std::size_t z,
    float minimumElevation,
    float maximumElevation,
    float waterLevel,
    float rawSample = 0.0f,
    float rawMinimum = 0.0f,
    float rawMaximum = 1.0f
);
