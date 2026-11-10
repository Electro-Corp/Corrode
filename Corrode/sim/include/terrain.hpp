#pragma once

#include <cstddef>
#include <iterator>
#include <vector>


class Terrain {
    public:
        Terrain(std::size_t width, std::size_t depth, float cellSize = 1.0f);

        std::size_t width() const noexcept;
        std::size_t depth() const noexcept;
        float cellSize() const noexcept;

        float heightAt(std::size_t x, std::size_t z) const;
        void setHeight(std::size_t x, std::size_t z, float height);
        

    private:
        std::size_t index(std::size_t x, std::size_t z) const;
        void validateCoordinates(std::size_t x, std::size_t z) const;

        std::size_t width_;
        std::size_t depth_;
        float cellSize_;

        std::vector<float> heights_;
};
