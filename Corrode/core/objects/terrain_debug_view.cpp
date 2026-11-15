#include <core/objects/terrain_debug_view.hpp>

namespace {

    constexpr std::size_t gridInterval = 16;

    float clampByte(float value) {
        if(value < 0.0f) return 0.0f;
        if(value > 255.0f) return 255.0f;
        return value;
    }

    RGB clampColor(RGB color) {
        return RGB{clampByte(color.r), clampByte(color.g), clampByte(color.b)};
    }

}

RGB terrainDebugColor(
    TerrainDebugView view,
    const Simulation::Terrain& terrain,
    std::size_t x,
    std::size_t z,
    float minimumElevation,
    float maximumElevation,
    float waterLevel
) {
    const float elevation = terrain.heightAt(x, z);

    switch(view) {
        case TerrainDebugView::WaterClassification:
            return terrain.belowWaterAt(x, z)
                ? RGB{255.0f, 0.0f, 255.0f}
                : RGB{0.0f, 255.0f, 0.0f};
        case TerrainDebugView::ElevationBands:
            if(elevation < waterLevel - 10.0f) return RGB{40.0f, 80.0f, 190.0f};
            if(elevation < waterLevel) return RGB{150.0f, 40.0f, 190.0f};
            if(elevation < waterLevel + 10.0f) return RGB{220.0f, 190.0f, 40.0f};
            return RGB{50.0f, 210.0f, 70.0f};
        case TerrainDebugView::HeightGradient: {
            const float range = maximumElevation - minimumElevation;
            const float t = range > 0.0f
                ? clampByte((elevation - minimumElevation) / range * 255.0f) / 255.0f
                : 0.0f;
            return RGB{
                40.0f + 180.0f * t,
                70.0f + 30.0f * t,
                190.0f - 150.0f * t
            };
        }
        case TerrainDebugView::CoordinateGrid:
            return ((x / gridInterval + z / gridInterval) % 2 == 0)
                ? RGB{230.0f, 230.0f, 230.0f}
                : RGB{35.0f, 35.0f, 35.0f};
    }

    return RGB{0.0f, 0.0f, 0.0f};
}
