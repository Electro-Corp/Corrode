/*
    Project Corrode Simulation Engine
    flat_generator.hpp - An implementation of TerrainGenerator that generates a flat plane
*/

// Simulation include
#include <terrain.hpp>
// C++ STD
#include <cmath>
#include <stdexcept>

namespace Simulation {

Terrain::Terrain(std::size_t width, std::size_t depth, float cellSize)
    : width_(width),
      depth_(depth),
      cellSize_(cellSize),
      cells_(width * depth) {
    if (width == 0 || depth == 0) {
        throw std::invalid_argument("Terrain dimensions must be greater than zero.");
    }

    if (cellSize <= 0.0f) {
        throw std::invalid_argument("Terrain cell size must be greater than zero.");
    }

    cellDiagonalSize_ = std::sqrt(2.0f) * cellSize;
}

std::size_t Terrain::width() const noexcept {
    return width_;
}

std::size_t Terrain::depth() const noexcept {
    return depth_;
}

float Terrain::cellSize() const noexcept {
    return cellSize_;
}

float Terrain::cellDiagonalSize() const noexcept {
    return cellDiagonalSize_;
}

bool Terrain::cellCoordinatesAt(
    float worldX,
    float worldZ,
    std::size_t& cellX,
    std::size_t& cellZ
) const noexcept {
    if(!std::isfinite(worldX) || !std::isfinite(worldZ) || worldX < 0.0f || worldZ < 0.0f) {
        return false;
    }

    const float terrainWidth = static_cast<float>(width_) * cellSize_;
    const float terrainDepth = static_cast<float>(depth_) * cellSize_;
    if(worldX >= terrainWidth || worldZ >= terrainDepth) {
        return false;
    }

    cellX = static_cast<std::size_t>(std::floor(worldX / cellSize_));
    cellZ = static_cast<std::size_t>(std::floor(worldZ / cellSize_));
    return true;
}

void Terrain::cellCenterAt(
    std::size_t cellX,
    std::size_t cellZ,
    float& worldX,
    float& worldZ
) const {
    validateCoordinates(cellX, cellZ);
    worldX = (static_cast<float>(cellX) + 0.5f) * cellSize_;
    worldZ = (static_cast<float>(cellZ) + 0.5f) * cellSize_;
}

float Terrain::surfaceHeightAt(std::size_t cellX, std::size_t cellZ) const {
    const TerrainCell& cell = cellAt(cellX, cellZ);
    return (
        cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::TopLeft)] +
        cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::TopRight)] +
        cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::BottomRight)] +
        cell.cornerHeights[static_cast<std::size_t>(TerrainCorner::BottomLeft)]
    ) / 4.0f;
}

float Terrain::heightAt(std::size_t x, std::size_t z) const {
    return cellAt(x, z).elevation;
}

void Terrain::setHeight(std::size_t x, std::size_t z, float height) {
    TerrainCell& cell = cellAt(x, z);
    cell.elevation = height;
    cell.cornerHeights.fill(height);
}

float Terrain::cornerHeightAt(std::size_t x, std::size_t z, TerrainCorner corner) const {
    return cellAt(x, z).cornerHeights[static_cast<std::size_t>(corner)];
}

void Terrain::setCornerHeight(std::size_t x, std::size_t z, TerrainCorner corner, float height) {
    cellAt(x, z).cornerHeights[static_cast<std::size_t>(corner)] = height;
}

bool Terrain::belowWaterAt(std::size_t x, std::size_t z) const {
    return cellAt(x, z).water.belowWater;
}

void Terrain::setBelowWater(std::size_t x, std::size_t z, bool belowWater) {
    cellAt(x, z).water.belowWater = belowWater;
}

TerrainCell& Terrain::cellAt(std::size_t x, std::size_t z) {
    validateCoordinates(x, z);
    return cells_[index(x, z)];
}

const TerrainCell& Terrain::cellAt(std::size_t x, std::size_t z) const {
    validateCoordinates(x, z);
    return cells_[index(x, z)];
}

std::size_t Terrain::index(std::size_t x, std::size_t z) const {
    return z * width_ + x;
}

void Terrain::validateCoordinates(std::size_t x, std::size_t z) const {
    if (x >= width_ || z >= depth_) {
        throw std::out_of_range("Terrain coordinate is outside terrain bounds.");
    }
}

} // SIMULATION
