#pragma once

#include <cstddef>

#include <common/rgb.hpp>
#include <sim/include/terrain.hpp>

enum class TerrainDebugView {
    WaterClassification,
    ElevationBands,
    HeightGradient,
    CoordinateGrid
};

RGB terrainDebugColor(
    TerrainDebugView view,
    const Simulation::Terrain& terrain,
    std::size_t x,
    std::size_t z,
    float minimumElevation,
    float maximumElevation,
    float waterLevel
);
