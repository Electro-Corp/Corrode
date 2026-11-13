/*
    Project Corrode Simulation Engine
    perlin_generator.hpp - An implementation of TerrainGenerator that uses Perlin noise
*/

#pragma once

#include <terrain_generator.hpp>

namespace Simulation {

    class PerlinTerrainGenerator final : public TerrainGenerator {
        public:
            explicit PerlinTerrainGenerator();

            void generate(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
        private:
            float height_;
    };

}