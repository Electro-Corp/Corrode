#include <core/objects/terrain_debug_view.hpp>

namespace {

    constexpr std::size_t gridInterval = 16;

    float clampByte(float value) {
        if(value < 0.0f) return 0.0f;
        if(value > 255.0f) return 255.0f;
        return value;
    }

}

RGB terrainDebugColor(
    TerrainDebugView view,
    const Simulation::Terrain& terrain,
    std::size_t x,
    std::size_t z,
    float minimumElevation,
    float maximumElevation,
    float waterLevel,
    float rawSample,
    float rawMinimum,
    float rawMaximum
) {
    switch(view) {
        case TerrainDebugView::WaterClassification:
            return terrain.belowWaterAt(x, z)
                ? RGB{35.0f, 25.0f, 255.0f}
                : RGB{0.0f, 255.0f, 0.0f};
        case TerrainDebugView::ElevationBands:
            {
            const float elevation = terrain.heightAt(x, z);
            if(elevation < waterLevel - 10.0f) return RGB{40.0f, 80.0f, 190.0f};
            if(elevation < waterLevel) return RGB{150.0f, 40.0f, 190.0f};
            if(elevation < waterLevel + 10.0f) return RGB{220.0f, 190.0f, 40.0f};
            return RGB{50.0f, 210.0f, 70.0f};
            }
        case TerrainDebugView::HeightGradient: {
            const float elevation = terrain.heightAt(x, z);
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
        case TerrainDebugView::FertilityGradient: {
            if(terrain.belowWaterAt(x, z)) {
                return RGB{35.0f, 100.0f, 235.0f};
            }
            const float fertility = clampByte(terrain.cellAt(x, z).soil.fertility * 255.0f) / 255.0f;
            return RGB{
                150.0f - 120.0f * fertility,
                70.0f + 185.0f * fertility,
                30.0f + 40.0f * fertility
            };
        }
        case TerrainDebugView::VegetationGradient: {
            if(terrain.belowWaterAt(x, z)) {
                return RGB{35.0f, 100.0f, 235.0f};
            }
            const float vegetation = clampByte(terrain.cellAt(x, z).vegetation.amount * 255.0f) / 255.0f;
            return RGB{
                70.0f - 50.0f * vegetation,
                35.0f + 185.0f * vegetation,
                15.0f + 30.0f * vegetation
            };
        }
        case TerrainDebugView::RawPerlinNoise: {
            const float range = rawMaximum - rawMinimum;
            const float normalized = range > 0.0f
                ? clampByte((rawSample - rawMinimum) / range * 255.0f) / 255.0f
                : 0.5f;
            const float grayscale = normalized * 255.0f;
            return RGB{grayscale, grayscale, grayscale};
        }
        case TerrainDebugView::Count:
            break;
    }

    return RGB{0.0f, 0.0f, 0.0f};
}
