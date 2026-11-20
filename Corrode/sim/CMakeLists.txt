add_library(simulation SHARED
    # Simulation Library
    source/environment.cpp
    source/entity.cpp
    source/world.cpp
    # Terrain
    source/terrain.cpp
    # Generators
    source/generators/flat_generator.cpp
    source/generators/perlin_noise.cpp
    source/generators/noise_generator.cpp
    # Passes
    source/passes/base_elevation_pass.cpp
    source/passes/water_level_pass.cpp
    source/passes/fertility_pass.cpp
    source/passes/vegetation_initialization_pass.cpp
    # Entities
    source/entities/basic_entity.cpp
    # Behaviors
    source/behavior.cpp
    source/behaviours/roam_behavior.cpp
    # source/behaviors/find_food_behavior.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/Corrode/sim/include)
include_directories(${CMAKE_SOURCE_DIR}/Corrode/)


target_include_directories(simulation
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(simulation
    
)
