/*
    Project Corrode Simulation Engine
    noise_generator.cpp - TerrainGenerator that uses noise
*/

// Sim includes
#include <generators/noise_generator.hpp>
// C++ STD includes

namespace Simulation {

    const char* NoiseTerrainGenerator::name() const {
        return "Noise Terrain";
    }

    void NoiseTerrainGenerator::generate(Terrain &terrain, const TerrainGenerationSettings &settings) const {
        baseElevationPass_.apply(terrain, settings);
        waterLevelPass_.apply(terrain, settings);

        // Final generator integration:
        // FertilityLevelPass fertilityLevelPass;
        // fertilityLevelPass.apply(terrain, settings);
    }

} // SIMULATION
