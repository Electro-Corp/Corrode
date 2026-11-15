/*
    Project Corrode Simulation Engine
    noise_generator.hpp - An implementation of TerrainGenerator that uses noise
*/

#pragma once

#include <terrain_generator.hpp>
#include <passes/base_elevation_pass.hpp>
#include <passes/water_level_pass.hpp>

namespace Simulation {

    class NoiseTerrainGenerator final : public TerrainGenerator {
        public:
            const char* name() const override;

            void generate(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
        private:
            BaseElevationPass baseElevationPass_;
            WaterLevelPass waterLevelPass_;
    };

}
