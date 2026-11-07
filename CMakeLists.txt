cmake_minimum_required(VERSION 3.23)
project(Corrode)

# Graphics library
add_subdirectory(Corrode/graphics)
add_subdirectory(Corrode/sim)


# Corrode.exe
add_executable(Corrode 
    Corrode/core/main.cpp
    Corrode/core/object.cpp
    
    # Objects
    Corrode/core/objects/testObject.cpp
)

# Add include
include_directories(Corrode)
include_directories(Corrode/graphics/include)
include_directories(Corrode/sim/include)


# Link the library to the executable
target_link_libraries(Corrode PRIVATE graphics simulation)

# Copy graphics lib
add_custom_command(TARGET Corrode POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:graphics>
        $<TARGET_FILE_DIR:Corrode>
)

# Copy simulation lib
add_custom_command(TARGET Corrode POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:simuoation>
        $<TARGET_FILE_DIR:Corrode>
)


if(MINGW)
    target_link_options(Corrode PRIVATE
        -static-libgcc
        -static-libstdc++
    )
endif()