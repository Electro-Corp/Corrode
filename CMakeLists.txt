cmake_minimum_required(VERSION 3.23)
project(Corrode)

# Graphics library
add_subdirectory(Corrode/graphics)

# Corrode.exe
add_executable(Corrode Corrode/core/main.cpp)

# Add include
include_directories(Corrode)

# Link the library to the executable
target_link_libraries(Corrode PRIVATE graphics)