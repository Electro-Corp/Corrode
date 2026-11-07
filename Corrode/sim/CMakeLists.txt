add_library(simulation SHARED
    # Simulation Library
    source/environment.cpp
    source/entity.cpp
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