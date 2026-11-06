add_library(graphics SHARED
    # Graphics Library
    source/graphics.cpp
    source/shader.cpp
    source/drawable.cpp
    source/scene.cpp
    source/glad.c
    # Drawables
    source/drawables/testTriangle.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/Corrode/graphics/include)
include_directories(${CMAKE_SOURCE_DIR}/Corrode/)


target_include_directories(graphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(graphics
    glfw3
)