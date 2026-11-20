/*
    Project Corrode Simulation Engine
    base_elevation_pass.cpp - Base elevation pass for terrain 
*/

#include <passes/base_elevation_pass.hpp>
#include <generators/perlin_noise.hpp>
#include <terrain.hpp>
#include <terrain_generator.hpp>

#include <cmath>

namespace Simulation {

    namespace {

        float sampleHeight(
            const PerlinNoise& perlin,
            std::size_t x,
            std::size_t z,
            std::size_t width,
            std::size_t depth,
            float frequency,
            const TerrainGenerationSettings& settings
        ) {
            double total = 0.0;
            double amplitude = 1.0;
            double octaveFrequency = frequency;
            double maxAmplitude = 0.0;
            for(int octave = 0; octave < settings.baseOctaves; octave++) {
                total += perlin.perlin(
                    static_cast<double>(x) / width * octaveFrequency,
                    static_cast<double>(z) / depth * octaveFrequency,
                    0.5
                ) * amplitude;
                maxAmplitude += amplitude;
                amplitude *= 0.6;
                octaveFrequency *= 2.0;
            }
            double normalizedNoise = maxAmplitude > 0.0 ? total / maxAmplitude : 0.0;
            double height = (normalizedNoise + 1.0) * 0.5;
            if(height < 0.0) height = 0.0;
            if(height > 1.0) height = 1.0;
            const float signedHeight = (static_cast<float>(height) - 0.5f) * settings.baseScale;
            const float redistributedMagnitude = std::pow(
                std::abs(signedHeight),
                settings.baseRedistribution
            );
            return std::copysign(redistributedMagnitude, signedHeight);
        }

    }

    void BaseElevationPass::apply(Terrain &terrain, const TerrainGenerationSettings &settings) const {
        PerlinNoise perlin(settings.seed);

        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                const std::size_t width = terrain.width();
                const std::size_t depth = terrain.depth();
                const float topLeft = sampleHeight(perlin, x, z, width, depth, settings.baseFrequency, settings);
                const float topRight = sampleHeight(perlin, x + 1, z, width, depth, settings.baseFrequency, settings);
                const float bottomRight = sampleHeight(perlin, x + 1, z + 1, width, depth, settings.baseFrequency, settings);
                const float bottomLeft = sampleHeight(perlin, x, z + 1, width, depth, settings.baseFrequency, settings);

                terrain.setCornerHeight(x, z, TerrainCorner::TopLeft, topLeft);
                terrain.setCornerHeight(x, z, TerrainCorner::TopRight, topRight);
                terrain.setCornerHeight(x, z, TerrainCorner::BottomRight, bottomRight);
                terrain.setCornerHeight(x, z, TerrainCorner::BottomLeft, bottomLeft);
                terrain.cellAt(x, z).elevation = topLeft;
            }
        }
    }

}
