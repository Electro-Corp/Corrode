/*
    Project Corrode Simulation Engine
    fertility_pass.cpp - Fertility pass on Terrain
*/

#include <generators/perlin_noise.hpp>
#include <passes/fertility_pass.hpp>
#include <terrain.hpp>
#include <terrain_generator.hpp>

#include <algorithm>
#include <cmath>

namespace Simulation {

void FertilityLevelPass::apply(Terrain& terrain, const TerrainGenerationSettings& settings) const {
    for (std::size_t z = 0; z < terrain.depth(); z++) {
        for (std::size_t x = 0; x < terrain.width(); x++) {
            TerrainCell& cell = terrain.cellAt(x, z);
            constexpr double SoilSeedOffset = 9187.0;
            constexpr float SoilFrequency = 0.35f;

            PerlinNoise soilNoiseGenerator(settings.seed + SoilSeedOffset);

            double rawNoise = soilNoiseGenerator.perlin(
                static_cast<double>(x) * terrain.cellSize() * SoilFrequency,
                static_cast<double>(z) * terrain.cellSize() * SoilFrequency, 0.5);

            float soilNoise = static_cast<float>((rawNoise + 1.0) * 0.5);
            soilNoise = std::max(0.0f, std::min(1.0f, soilNoise));

            // TODO Move to own function and add math
            float landFactor = terrain.belowWaterAt(x, z) ? 0.0f : 1.0f;
            float slopePenalty = calculateSlopePenalty(cell, terrain.cellSize());
            float moistureBonus = calculateMoistureBonus();
            // TODO add more factors


            float fertility = landFactor * (0.25f + 0.75f * soilNoise);
            cell.soil.fertility = fertility * landFactor * slopePenalty * moistureBonus;
        }
    }
}

float FertilityLevelPass::calculateMoistureBonus() const {
    // TODO add functionality
    return 1.0f;
}
float FertilityLevelPass::calculateSlopePenalty(const TerrainCell& cell, float cellSize) const {
    const float h00 = cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::TopLeft)];
    const float h10 = cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::TopRight)];
    const float h11 = cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::BottomRight)];
    const float h01 = cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::BottomLeft)];

    const float riseX = ((h10 + h11) - (h00 + h01)) / (2.0f * cellSize);
    const float riseZ = ((h01 + h11) - (h00 + h10)) / (2.0f * cellSize);

    const float slopeMagnitude = std::sqrt(riseX * riseX + riseZ * riseZ);

    // const float slopePenalty = std::max(0.5f, slopeMagnitude);
    // return std::pow(slopePenalty, -0.5f);

    constexpr float halfPi = 1.57079632679f;
    const float normalizedSlope = std::atan(slopeMagnitude) / halfPi;
    return 1.0f - 0.75f * normalizedSlope;
}
} // namespace Simulation
