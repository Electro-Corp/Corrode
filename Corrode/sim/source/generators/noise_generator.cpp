/*
    Project Corrode Simulation Engine
    noise_generator.cpp - TerrainGenerator that uses noise
*/

// Sim includes
#include <generators/noise_generator.hpp>
#include <generators/perlin_noise.hpp>
#include <terrain.hpp>
// C++ STD includes

namespace Simulation {

    const char* NoiseTerrainGenerator::name() const {
        return "Noise Terrain";
    }

    void NoiseTerrainGenerator::generate(Terrain &terrain, const TerrainGenerationSettings &settings) const {
        PerlinNoise perlin(settings.seed);

        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                double total = 0.0;
                double amplitude = 1.0;
                double octaveFrequency = settings.frequency;
                double maxAmplitude = 0.0;
                for(int octave = 0; octave < settings.octaves; octave++) {
//                    total += perlin.perlin((double) x / terrain.width() * octaveFrequency, (double) z / terrain.depth() * octaveFrequency, 0.5) * 100.0f;
                    total += perlin.perlin((double) x / terrain.width() * octaveFrequency, (double) z / terrain.depth() * octaveFrequency, 0.5) * amplitude;
                    maxAmplitude += amplitude;
                    amplitude *= 0.9;
                    octaveFrequency *= 2.0;
                }
                double normalizedNoise = maxAmplitude > 0.0 ? total / maxAmplitude : 0.0;
                double height = (normalizedNoise + 1.0) * 0.5;
                if(height < 0.0) height = 0.0;
                if(height > 1.0) height = 1.0;
                terrain.setHeight(x, z, (static_cast<float>(height) - 0.5f) * settings.scale);
            }
        }
    }

} // SIMULATION
