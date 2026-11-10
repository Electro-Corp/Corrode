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
    };

    class TerrainGenerator {
        public:
            virtual ~TerrainGenerator() = default;

            virtual void generate(
                Terrain& terrain, 
                const TerrainGenerationSettings& settings
            ) const = 0;
    };

}