/*
    Project Corrode main
*/
// C++ STD
#include <iostream>
#include <memory>
// Core includes
#include <util/args.hpp>
#include <util/log.hpp>
// Graphics Engine includes
#include <graphics/include/graphics.hpp>

// Global pointer for the graphics engine
std::unique_ptr<Rendering::GraphicsEngine> graphicsEngine;

int main(int argv, char* args[]){
    // Generate settings
    Rendering::EngineInitOptions gOptions = {"Corrode", 600, 800};
    gOptions.clearColor = {12.0f, 50.0f, 100.0f, 255.0f};
    // Check if args override
    if(Util::doesParamExist("-width", argv, args)){
        try { gOptions.w = std::stoi(Util::getParam("-width", argv, args)); }
        catch (std::invalid_argument e) { 
            Util::Log("main", "Invalid argument to -width!\n");
            return -1;
        }
    }
    if(Util::doesParamExist("-height", argv, args)){
        try { gOptions.h = std::stoi(Util::getParam("-height", argv, args)); }
        catch (std::invalid_argument e) { 
            Util::Log("main", "Invalid argument to -height!\n");
            return -1;
        }
    }
    // Create graphics engine
    graphicsEngine = std::make_unique<Rendering::GraphicsEngine>(gOptions);

    // Make this loop timer based later
    while(1){
        if(graphicsEngine->tick() < 0) break;
    }

    return 0;
}