/*
    Project Corrode Simulation Engine
    perlin_generator.cpp - TerrainGenerator that uses Perlin noise
*/

// Sim includes
#include <generators/perlin_generator.hpp>
#include <terrain.hpp>
// C++ STD includes
#include <cstdio>
#include <numeric>
#include <random>
#include <algorithm>

namespace Simulation {

    PerlinTerrainGenerator::PerlinTerrainGenerator(double seed) {
        // Generate random permutation values based on seed
        std::mt19937 gen(seed);

        // Create vector and fill with values 0-255
        std::vector<int> values(256);
        std::iota(values.begin(), values.end(), 0);
        // Shuffle it
        std::shuffle(values.begin(), values.end(), gen);

        for(int i = 0; i < 512; i++) this->p[i] = values[i % 256];
    }

    void PerlinTerrainGenerator::generate(Terrain &terrain, const TerrainGenerationSettings &settings) const {
        for(std::size_t z = 0; z < terrain.depth(); z++) {
            for(std::size_t x = 0; x < terrain.width(); x++) {
                // Preform octave generation
                double total = 0.0, f = 1.0, a = 1.0, maxValue = 0.0;
                for(int i = 0; i < settings.octaves; i++){
                    total += perlin((double) x / terrain.width(), (double) z / terrain.depth(), 0.5) * 100.0;
                    maxValue += a;
                    a *= 0.9;
                    f *= 2;
                }
                terrain.setHeight(x, z, total / maxValue);
            }
        }
    }
    
    // Adapted from https://adrianb.io/2014/08/09/perlinnoise.html's C# implementation, which itself is adapted 
    // from Ken Perlin's 2002 Java implementation 
    double PerlinTerrainGenerator::perlin(double x, double y, double z) const{
        // Unit cube positions
        int xI = (int) x & 255, yI = (int) y & 255, zI = (int) z & 255;
        double xF = x - (int)x, yF = y - (int)y, zF = z - (int)z;
        // Fade values
        double u = fade(xF), v = fade(yF), w = fade(zF);

        // Perlin noise hash function (ugly but it works so)
        int aaa, aba, aab, abb, baa, bba, bab, bbb;
        aaa = p[p[p[    xI ]+    yI ]+    zI ];
        aba = p[p[p[    xI ]+ yI + 1]+    zI ];
        aab = p[p[p[    xI ]+    yI ]+ zI + 1];
        abb = p[p[p[    xI ]+ yI + 1]+ zI + 1];
        baa = p[p[p[xI + 1]+    yI ]+    zI ];
        bba = p[p[p[xI + 1]+ yI + 1]+    zI ];
        bab = p[p[p[xI + 1]+    yI ]+ zI + 1];
        bbb = p[p[p[xI + 1]+ yI + 1]+ zI + 1];

        // Generate the gradients
        double x1 = lerp(grad(aaa, xF, yF, zF), 
                         grad(baa, xF - 1, yF, zF), 
                         u);
        double x2 = lerp(grad(aba, xF, yF - 1, zF), 
                         grad(bba, xF - 1, yF - 1, zF), 
                         u);

        // First two gradients lerped
        double y1 = lerp(x1, x2, v);
        
        x1 = lerp(grad(aab, xF, yF, zF - 1), 
                  grad(bab, xF - 1, yF, zF - 1), 
                  u);

        x2 = lerp(grad(abb, xF, yF - 1, zF - 1), 
                  grad(bbb, xF - 1, yF - 1, zF - 1), 
                  u);

        // Second two gradients lerped
        double y2 = lerp(x1, x2, v);

        return lerp(y1, y2, w); // lerp the two y's
    }

} // SIMULATION