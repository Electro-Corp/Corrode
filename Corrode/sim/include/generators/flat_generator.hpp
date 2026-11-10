#pragma once

#include "terrain_generator.hpp"

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
