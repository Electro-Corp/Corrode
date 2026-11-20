/*
    Project Corrode Simulation Engine
    terrain_generator.hpp - Abstract class for a terrain generator
*/

#pragma once

namespace Simulation{

    class Terrain;

    struct TerrainGenerationSettings {
        double seed = 0;
        float baseFrequency = 1.0f;
        int baseOctaves = 8;
        float baseRedistribution = 1.2f;
        float baseScale = 50.0f;
        float water_level = 0.0f;
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
