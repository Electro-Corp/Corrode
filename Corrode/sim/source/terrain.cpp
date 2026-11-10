/*
    Project Corrode Simulation Engine
    flat_generator.hpp - An implementation of TerrainGenerator that generates a flat plane
*/

// Simulation include
#include <terrain.hpp>
// C++ STD
#include <stdexcept>

namespace Simulation {

Terrain::Terrain(std::size_t width, std::size_t depth, float cellSize)
    : width_(width),
      depth_(depth),
      cellSize_(cellSize),
      heights_(width * depth, 0.0f) {
    if (width == 0 || depth == 0) {
        throw std::invalid_argument("Terrain dimensions must be greater than zero.");
    }

    if (cellSize <= 0.0f) {
        throw std::invalid_argument("Terrain cell size must be greater than zero.");
    }
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

float Terrain::heightAt(std::size_t x, std::size_t z) const {
    validateCoordinates(x, z);
    return heights_[index(x, z)];
}

void Terrain::setHeight(std::size_t x, std::size_t z, float height) {
    validateCoordinates(x, z);
    heights_[index(x, z)] = height;
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