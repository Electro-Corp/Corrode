/*
    Project Corrode Simulation Engine
    terrain_pass.hpp - Abstract classes for terrain passes
*/

#pragma once

namespace Simulation {

    class Terrain;
    struct TerrainGenerationSettings;

    class TerrainPass {
        public:
            virtual ~TerrainPass() = default;

            virtual void apply(
                Terrain& terrain,
                const TerrainGenerationSettings& settings
            ) const = 0;
    };

}
