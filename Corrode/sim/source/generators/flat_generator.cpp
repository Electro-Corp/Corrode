#include "generators/flat_generator.hpp"
#include "terrain.hpp"
#include <cstdio>

FlatTerrainGenerator::FlatTerrainGenerator(float height)
    : height_(height) {}

    void FlatTerrainGenerator::generate(Terrain &terrain, const TerrainGenerationSettings &settings) const {
        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                terrain.setHeight(x, z, height_);
            }
        }
    }
