/*
    Project Corrode main
*/
// C++ STD
#include <iostream>
#include <memory>
// Graphics Engine include 
#include <graphics/include/graphics.hpp>

// Global pointer for the graphics engine
std::unique_ptr<Rendering::GraphicsEngine> graphicsEngine;

int main(int argv, char* args[]){
    // Generate settings
    Rendering::EngineInitOptions gOptions = {"Corrode", 600, 800};
    gOptions.clearColor = {12.0f, 50.0f, 100.0f, 255.0f};

    graphicsEngine = std::make_unique<Rendering::GraphicsEngine>(gOptions);

    while(1){
        if(graphicsEngine->tick() < 0) break;
    }

    return 0;
}