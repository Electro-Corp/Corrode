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
    graphicsEngine = std::make_unique<Rendering::GraphicsEngine>();

    while(1){
        if(graphicsEngine->tick() < 0) break;
    }

    return 0;
}