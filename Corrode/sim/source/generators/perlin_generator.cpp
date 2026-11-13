/*
    Project Corrode Simulation Engine
    perlin_generator.cpp - TerrainGenerator that uses Perlin noise
*/

#include <generators/perlin_generator.hpp>
#include <terrain.hpp>
#include <cstdio>

namespace Simulation {

    PerlinTerrainGenerator::PerlinTerrainGenerator() {}

    void PerlinTerrainGenerator::generate(Terrain &terrain, const TerrainGenerationSettings &settings) const {
        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                terrain.setHeight(x, z, 0); // 0 with computed height
            }
        }
    }

} // SIMULATION