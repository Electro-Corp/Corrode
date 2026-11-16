/*
    Project Corrode Simulation Engine
    water_level_pass.cpp - Water pass on Terrain
*/

#include <passes/water_level_pass.hpp>
#include <terrain.hpp>
#include <terrain_generator.hpp>

namespace Simulation {

    void WaterLevelPass::apply(Terrain& terrain, const TerrainGenerationSettings& settings) const {
        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                TerrainCell& cell = terrain.cellAt(x, z);
                // In the future change this to be a dynamic value or something
                // to create more interesting terrain
                // Possibly something like mountain lakes at different elevations
                // or something
                cell.water.belowWater = cell.elevation < settings.water_level;
            }
        }
    }

}
