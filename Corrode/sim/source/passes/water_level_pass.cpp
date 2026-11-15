#include <passes/water_level_pass.hpp>
#include <terrain.hpp>
#include <terrain_generator.hpp>

namespace Simulation {

    void WaterLevelPass::apply(Terrain& terrain, const TerrainGenerationSettings& settings) const {
        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                TerrainCell& cell = terrain.cellAt(x, z);
                cell.belowWater = cell.elevation < settings.water_level;
            }
        }
    }

}
