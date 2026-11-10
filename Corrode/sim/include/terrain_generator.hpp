#pragma once

#include <cstdint>

class Terrain;

struct TerrainGenerationSettings {
    std::uint32_t seed = 0;
};

class TerrainGenerator {
    public:
        virtual ~TerrainGenerator() = default;

        virtual void generate(
            Terrain& terrain, 
            const TerrainGenerationSettings& settings
        ) const = 0;
};
