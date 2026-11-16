/*
    Project Corrode Simulation Engine
    vegetation_initialization_pass.hpp - Initializes edible vegetation on Terrain
*/

#pragma once

#include <terrain_pass.hpp>

namespace Simulation {

    class VegetationInitializationPass final : public TerrainPass {
        public:
            void apply(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
    };

}
