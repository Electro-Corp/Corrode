/*
    Project Corrode Simulation Engine
    terrain_generator.hpp - Abstract class for a terrain generator
*/

#pragma once

#include <cstdint>

namespace Simulation{

    class Terrain;

    struct TerrainGenerationSettings {
        std::uint32_t seed = 0;
        float frequency = 1.0f;
        int octaves = 8;
    };

    class TerrainGenerator {
        public:
            virtual ~TerrainGenerator() = default;

            virtual const char* name() const = 0;

            virtual void generate(
                Terrain& terrain, 
                const TerrainGenerationSettings& settings
            ) const = 0;
    };

}
