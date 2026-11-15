/*
    Project Corrode Simulation Engine
    base_elevation_pass.hpp - Base elevation pass for terrain 
*/

#pragma once

#include <terrain_pass.hpp>

namespace Simulation {

    class BaseElevationPass final : public TerrainPass {
        public:
            void apply(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
    };

}
