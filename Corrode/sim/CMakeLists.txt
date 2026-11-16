add_library(simulation SHARED
    # Simulation Library
    source/environment.cpp
    source/entity.cpp
    # Terrain
    source/terrain.cpp
    source/generators/flat_generator.cpp
    source/generators/perlin_noise.cpp
    source/generators/noise_generator.cpp
    source/passes/base_elevation_pass.cpp
    source/passes/water_level_pass.cpp
    source/passes/fertility_pass.cpp
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
