/*
    Project Corrode Simulation Engine
    terrain.hpp - Root class for generating the terrain
*/
#pragma once

#include <cstddef>
#include <vector>
#include <terrain_cell.hpp>

namespace Simulation{

    enum class TerrainCorner {
        TopLeft,
        TopRight,
        BottomRight,
        BottomLeft
    };

    class Terrain {
        public:
            Terrain(std::size_t width, std::size_t depth, float cellSize = 1.0f);

            std::size_t width() const noexcept;
            std::size_t depth() const noexcept;
            float cellSize() const noexcept;
            float cellDiagonalSize() const noexcept;

            bool cellCoordinatesAt(
                float worldX,
                float worldZ,
                std::size_t& cellX,
                std::size_t& cellZ
            ) const noexcept;
            void cellCenterAt(
                std::size_t cellX,
                std::size_t cellZ,
                float& worldX,
                float& worldZ
            ) const;
            float surfaceHeightAt(std::size_t cellX, std::size_t cellZ) const;

            float heightAt(std::size_t x, std::size_t z) const;
            void setHeight(std::size_t x, std::size_t z, float height);
            float cornerHeightAt(std::size_t x, std::size_t z, TerrainCorner corner) const;
            void setCornerHeight(std::size_t x, std::size_t z, TerrainCorner corner, float height);

            bool belowWaterAt(std::size_t x, std::size_t z) const;
            void setBelowWater(std::size_t x, std::size_t z, bool belowWater);

            TerrainCell& cellAt(std::size_t x, std::size_t z);
            const TerrainCell& cellAt(std::size_t x, std::size_t z) const;
            

        private:
            std::size_t index(std::size_t x, std::size_t z) const;
            void validateCoordinates(std::size_t x, std::size_t z) const;

            std::size_t width_;
            std::size_t depth_;
            float cellSize_;
            float cellDiagonalSize_;

            std::vector<TerrainCell> cells_;
    };
}
