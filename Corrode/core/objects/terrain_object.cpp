/*
    Project Corrode
    object.hpp - Extends Object to preform tests
*/
// Core
#include <core/objects/terrain_debug_view.hpp>
#include <core/objects/terrain_object.hpp>
// Common
#include <common/log.hpp>
#include <common/rgb.hpp>
// Graphics
#include <graphics/include/drawables/mesh.hpp>
// Terrain/simulation
#include <sim/include/generators/noise_generator.hpp>
#include <sim/include/generators/perlin_noise.hpp>
#include <sim/include/passes/fertility_pass.hpp>
#include <sim/include/passes/vegetation_initialization_pass.hpp>
// glad
#include <glad.h>
// C++ STD
#include <limits>
#include <vector>

TerrainObject::TerrainObject() {
    Util::Log("TerrainObject::TerrainObject", "Generating Terrain, please wait...");
    // Generate terrain
    this->terrain = std::make_shared<Simulation::Terrain>(256, 256);
    Simulation::NoiseTerrainGenerator noiseTerrainGenerator;

    Simulation::TerrainGenerationSettings terrainSettings{
        4323122924, // Seed
        0.6f,       // Base frequency
        5,          // Base octaves
        1.1f,       // Base redistribution (increase to make height differences more extreme)
        160.0f,     // Scale
        0.0f        // Water Height
    };
    terrainSettings_ = terrainSettings;

    noiseTerrainGenerator.generate(*(this->terrain), terrainSettings);

    constexpr bool enableExperimentalFertility = true;
    if (enableExperimentalFertility) {
        Simulation::FertilityLevelPass fertilityLevelPass;
        fertilityLevelPass.apply(*(this->terrain), terrainSettings);
        Simulation::VegetationInitializationPass vegetationInitializationPass;
        vegetationInitializationPass.apply(*(this->terrain), terrainSettings);
    }

    //
    // What follows is a lot of stuff
    // that should be moved into its own function probabbly
    //

    std::size_t width = terrain->width();
    std::size_t depth = terrain->depth();
    const bool rawNoiseView = activeDebugView_ == TerrainDebugView::RawPerlinNoise;
    float minimumElevation = terrain->heightAt(0, 0);
    float maximumElevation = minimumElevation;
    for (std::size_t z = 0; z < depth; z++) {
        for (std::size_t x = 0; x < width; x++) {
            const float elevation = terrain->heightAt(x, z);
            if (elevation < minimumElevation)
                minimumElevation = elevation;
            if (elevation > maximumElevation)
                maximumElevation = elevation;
        }
    }
    minimumElevation_ = minimumElevation;
    maximumElevation_ = maximumElevation;

    // Initialize diffuse texture
    unsigned int diffuseID;
    glGenTextures(1, &diffuseID);
    diffuseTextureID_ = diffuseID;
    textures.emplace_back(diffuseID, std::string("texture_diffuse"), std::string("null"));
    // Initialize specular texture
    unsigned int specularID;
    glGenTextures(1, &specularID);
    textures.emplace_back(specularID, std::string("texture_specular"), std::string("null"));
    // Temporary texture storage
    std::vector<unsigned char> diffuseData(width * depth * 3);
    std::vector<unsigned char> specularData(width * depth * 3);
    rawSamples_.clear();
    double rawMinimum = 0.0f;
    double rawMaximum = 0.0f;
    Simulation::PerlinNoise rawPerlinNoise(terrainSettings.seed);
    rawSamples_.resize(width * depth);
    rawMinimum = std::numeric_limits<double>::max();
    rawMaximum = std::numeric_limits<double>::lowest();
    for (std::size_t z = 0; z < depth; z++) {
        for (std::size_t x = 0; x < width; x++) {
                double total = 0.0;
                double amplitude = 1.0;
                double octaveFrequency = terrainSettings.baseFrequency;
                double maxAmplitude = 0.0;
                for (int octave = 0; octave < terrainSettings.baseOctaves; octave++) {
                    total += rawPerlinNoise.perlin(static_cast<double>(x) / width * octaveFrequency,
                                                   static_cast<double>(z) / depth * octaveFrequency,
                                                   0.5) * amplitude;
                    maxAmplitude += amplitude;
                    amplitude *= 0.6;
                    octaveFrequency *= 2.0;
                }

                double normalizedNoise = maxAmplitude > 0.0 ? total / maxAmplitude : 0.0;
                double height = (normalizedNoise + 1.0) * 0.5;
                if (height < 0.0)
                    height = 0.0;
                if (height > 1.0)
                    height = 1.0;

                height = std::pow(height, terrainSettings.baseRedistribution);
                rawMinimum = std::min(height, rawMinimum);
                rawMaximum = std::max(height, rawMaximum);
                rawSamples_[x + z * width] = static_cast<float>(height);
        }
    }
    rawMinimum_ = static_cast<float>(rawMinimum);
    rawMaximum_ = static_cast<float>(rawMaximum);

    // Generate vertices (and texture) based on terrain gen
    for (std::size_t z = 0; z < depth; z++) {
        for (std::size_t x = 0; x < width; x++) {
            const float topLeft = terrain->cornerHeightAt(x, z, Simulation::TerrainCorner::TopLeft);
            const float topRight = terrain->cornerHeightAt(x, z, Simulation::TerrainCorner::TopRight);
            const float bottomRight = terrain->cornerHeightAt(x, z, Simulation::TerrainCorner::BottomRight);
            const float bottomLeft = terrain->cornerHeightAt(x, z, Simulation::TerrainCorner::BottomLeft);
            const float height = terrain->heightAt(x, z);
            const bool belowWater = terrain->belowWaterAt(x, z);

            RGB color = terrainDebugColor(activeDebugView_, *terrain, x, z, minimumElevation,
                                          maximumElevation, terrainSettings.water_level,
                                          rawNoiseView ? rawSamples_[x + z * width] : 0.0f,
                                          rawMinimum, rawMaximum);

            const float xPosition = x * terrain->cellSize();
            const float zPosition = z * terrain->cellSize();
            const float xTexture = static_cast<float>(x) / static_cast<float>(width);
            const float zTexture = static_cast<float>(z) / static_cast<float>(depth);
            const float xTextureNext = static_cast<float>(x + 1) / static_cast<float>(width);
            const float zTextureNext = static_cast<float>(z + 1) / static_cast<float>(depth);

            vertices.emplace_back(glm::vec3(xPosition, topLeft, zPosition),
                                  glm::vec2(xTexture, zTexture), glm::vec3(0.0, 0.0, 0.0));

            vertices.emplace_back(glm::vec3(xPosition + terrain->cellSize(), topRight, zPosition),
                                  glm::vec2(xTextureNext, zTexture), glm::vec3(0.0, 0.0, 0.0));

            vertices.emplace_back(glm::vec3(xPosition + terrain->cellSize(), bottomRight,
                                            zPosition + terrain->cellSize()),
                                  glm::vec2(xTextureNext, zTextureNext), glm::vec3(0.0, 0.0, 0.0));

            vertices.emplace_back(glm::vec3(xPosition, bottomLeft, zPosition + terrain->cellSize()),
                                  glm::vec2(xTexture, zTextureNext), glm::vec3(0.0, 0.0, 0.0));

            // Generate texture pixel
            unsigned int location = (x + (z * width)) * 3;
            diffuseData[location] = static_cast<unsigned char>(color.r);
            diffuseData[location + 1] = static_cast<unsigned char>(color.g);
            diffuseData[location + 2] = static_cast<unsigned char>(color.b);

            // Specular
            specularData[location] = static_cast<unsigned char>((50 + height) * (belowWater));
            specularData[location + 1] = static_cast<unsigned char>((50 + height) * (belowWater));
            specularData[location + 2] = static_cast<unsigned char>((50 + height) * (belowWater));
        }
    }

    // Copy data to diffuse texture
    glBindTexture(GL_TEXTURE_2D, diffuseID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, depth, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 diffuseData.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Copy data to specular texture
    glBindTexture(GL_TEXTURE_2D, specularID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, depth, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 specularData.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate indices
    // Adapted from
    // https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/indexbuffers/Tutorial%208%20-%20Index%20Buffers.pdf
    for (std::size_t z = 0; z < depth; z++) {
        for (std::size_t x = 0; x < width; x++) {
            const std::uint32_t base = static_cast<std::uint32_t>((z * width + x) * 4);
            const std::uint32_t a = base;
            const std::uint32_t b = base + 1;
            const std::uint32_t c = base + 2;
            const std::uint32_t d = base + 3;

            ind.push_back(c);
            ind.push_back(b);
            ind.push_back(a);

            ind.push_back(a);
            ind.push_back(d);
            ind.push_back(c);
        }
    }

    // Generate normals
    for (std::size_t i = 0; i < ind.size(); i += 3) {
        std::uint32_t a = ind[i], b = ind[i + 1], c = ind[i + 2];
        // Generate normal
        glm::vec3 normal =
            glm::cross(vertices[b].pos - vertices[a].pos, vertices[c].pos - vertices[a].pos);
        // Add normal
        vertices[a].normal = normal;
        vertices[b].normal = normal;
        vertices[c].normal = normal;
    }

    // Shader
    Rendering::Shader* vertex =
        new Rendering::Shader("../assets/shaders/terrain.vert", Rendering::VERTEX);
    Rendering::Shader* fragment =
        new Rendering::Shader("../assets/shaders/terrain.frag", Rendering::FRAGMENT);
    this->shaderProgram = std::make_shared<Rendering::ShaderProgram>(vertex, fragment);
    glUseProgram(this->shaderProgram->getShaderProgram());
    this->shaderProgram->setBool("rawNoiseUnlit", rawNoiseView);
    this->shaderProgram->setBool("rawNoiseFlat", rawNoiseView);

    // Final drawable
    this->drawable = std::make_shared<Drawable::Mesh>(vertices, ind, textures, shaderProgram);

    Util::Log("TerrainObject::TerrainObject", "Terrain generated.");
}

void TerrainObject::tick() {}

void TerrainObject::updateDebugModeUniforms() {
    const bool rawNoiseView = activeDebugView_ == TerrainDebugView::RawPerlinNoise;
    glUseProgram(shaderProgram->getShaderProgram());
    shaderProgram->setBool("rawNoiseUnlit", rawNoiseView);
    shaderProgram->setBool("rawNoiseFlat", rawNoiseView);
}

void TerrainObject::updateDebugTexture() {
    const std::size_t width = terrain->width();
    const std::size_t depth = terrain->depth();
    std::vector<unsigned char> diffuseData(width * depth * 3);
    for(std::size_t z = 0; z < depth; z++) {
        for(std::size_t x = 0; x < width; x++) {
            const RGB color = terrainDebugColor(
                activeDebugView_, *terrain, x, z,
                minimumElevation_, maximumElevation_, terrainSettings_.water_level,
                activeDebugView_ == TerrainDebugView::RawPerlinNoise
                    ? rawSamples_[x + z * width]
                    : 0.0f,
                rawMinimum_, rawMaximum_
            );
            const std::size_t location = (x + z * width) * 3;
            diffuseData[location] = static_cast<unsigned char>(color.r);
            diffuseData[location + 1] = static_cast<unsigned char>(color.g);
            diffuseData[location + 2] = static_cast<unsigned char>(color.b);
        }
    }
    glBindTexture(GL_TEXTURE_2D, diffuseTextureID_);
    glTexSubImage2D(
        GL_TEXTURE_2D, 0, 0, 0, width, depth,
        GL_RGB, GL_UNSIGNED_BYTE, diffuseData.data()
    );
    glGenerateMipmap(GL_TEXTURE_2D);
}

void TerrainObject::tick(GLFWwindow* window) {
    const bool leftPressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    const bool rightPressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    constexpr int viewCount = static_cast<int>(TerrainDebugView::Count);

    if(leftPressed && !previousLeftPressed_) {
        const int current = static_cast<int>(activeDebugView_);
        activeDebugView_ = static_cast<TerrainDebugView>((current + viewCount - 1) % viewCount);
        updateDebugTexture();
        updateDebugModeUniforms();
    } else if(rightPressed && !previousRightPressed_) {
        const int current = static_cast<int>(activeDebugView_);
        activeDebugView_ = static_cast<TerrainDebugView>((current + 1) % viewCount);
        updateDebugTexture();
        updateDebugModeUniforms();
    }

    previousLeftPressed_ = leftPressed;
    previousRightPressed_ = rightPressed;
}
