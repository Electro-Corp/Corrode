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
