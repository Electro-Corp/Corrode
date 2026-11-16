/*
    Project Corrode Simulation Engine
    fertility_pass.hpp - Fertility pass on Terrain
*/

#pragma once

#include "terrain_cell.hpp"
#include <terrain_pass.hpp>

namespace Simulation {

    class FertilityLevelPass final : public TerrainPass {
        public:
            void apply(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
        private:
            float calculateSlopePenalty(const TerrainCell& cell, float cellSize) const;
            float calculateMoistureBonus() const;
    };

}
