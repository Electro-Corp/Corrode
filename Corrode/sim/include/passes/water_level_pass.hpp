/*
    Project Corrode Simulation Engine
    water_level_pass.hpp - Water pass on Terrain
*/

#pragma once

#include <terrain_pass.hpp>

namespace Simulation {

    class WaterLevelPass final : public TerrainPass {
        public:
            void apply(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
    };

}
