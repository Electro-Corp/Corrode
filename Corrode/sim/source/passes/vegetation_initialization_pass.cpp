/*
    Project Corrode Simulation Engine
    vegetation_initialization_pass.cpp - Initializes edible vegetation on Terrain
*/

#include <algorithm>
#include <passes/vegetation_initialization_pass.hpp>
#include <terrain.hpp>
#include <terrain_generator.hpp>

namespace Simulation {

    void VegetationInitializationPass::apply(
        Terrain& terrain,
        const TerrainGenerationSettings& settings
    ) const {
        (void) settings;
        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                TerrainCell& cell = terrain.cellAt(x, z);
                const float amount = terrain.belowWaterAt(x, z)
                    ? 0.0f
                    : cell.soil.fertility;
                cell.vegetation.amount = std::max(0.0f, std::min(1.0f, amount));
            }
        }
    }

}
