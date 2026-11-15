/*
    Project Corrode Simulation Engine
    perlin_generator.hpp - An implementation of TerrainGenerator that uses Perlin noise
*/

#pragma once

#include <terrain_generator.hpp>

#define CELL_SIZE 4

namespace Simulation {

    class PerlinTerrainGenerator final : public TerrainGenerator {
        public:
            explicit PerlinTerrainGenerator(double seed);

            void generate(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const override;
        private:
            // Perlin functions
            double perlin(double x, double y, double z) const;
            
            // Ken Perlin's fade function
            static double fade(double t){ return t * t * t * (t * (t * 6 - 15) + 10); }
            // Lerp between two values 
            static double lerp(double a, double b, double t) { return a + t * (b - a); }

            // Source: http://riven8192.blogspot.com/2010/08/calculate-perlinnoise-twice-as-fast.html
            static double grad(int hash, double x, double y, double z) {
                switch(hash & 0xF) {
                    case 0x0: return  x + y;
                    case 0x1: return -x + y;
                    case 0x2: return  x - y;
                    case 0x3: return -x - y;
                    case 0x4: return  x + z;
                    case 0x5: return -x + z;
                    case 0x6: return  x - z;
                    case 0x7: return -x - z;
                    case 0x8: return  y + z;
                    case 0x9: return -y + z;
                    case 0xA: return  y - z;
                    case 0xB: return -y - z;
                    case 0xC: return  y + x;
                    case 0xD: return -y + z;
                    case 0xE: return  y - x;
                    case 0xF: return -y - z;
                    default: return 0; // never happens
                }
            }

            int p[512];
    };

}