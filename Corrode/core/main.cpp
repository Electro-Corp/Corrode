/*
    Project Corrode main
*/
// C++ STD
#include <iostream>
// Graphics Engine include 
#include <graphics/include/graphics.hpp>

// Global pointer for the graphics engine
Rendering::GraphicsEngine* graphicsEngine;

int main(int args, char* argv[]){
    graphicsEngine = new Rendering::GraphicsEngine();

    while(1){
        if(graphicsEngine->tick() < 0) break;
    }

    delete(graphicsEngine);

    return 0;
}