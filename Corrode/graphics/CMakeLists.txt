add_library(graphics SHARED
    source/graphics.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/Corrode/graphics/include)

target_include_directories(graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(graphics
    glfw3
)