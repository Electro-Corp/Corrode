/*
    Project Corrode Simulation Engine
    flat_generator.hpp - An implementation of TerrainGenerator that generates a flat plane
*/

#pragma once

#include <terrain_generator.hpp>

namespace Simulation {

    class FlatTerrainGenerator final : public TerrainGenerator {
        public:
            explicit FlatTerrainGenerator(float height = 0.0f);

            void generate(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
        private:
            float height_;
    };

}