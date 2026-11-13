/*
    Project Corrode main
*/
// C++ STD
#include <memory>
// Core includes
#include <core/args.hpp>
#include <common/log.hpp>
// Graphics Engine includes
#include <graphics/include/graphics.hpp>
#include <graphics/include/scene.hpp>
#include <graphics/include/camera.hpp>
// Objects
#include <core/objects/test_object.hpp>
#include <core/objects/terrain_object.hpp>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

// Global pointer for the graphics engine
std::unique_ptr<Rendering::GraphicsEngine> graphicsEngine;

int main(int argv, char* args[]){
    // Generate settings
    Rendering::EngineInitOptions gOptions = {"Corrode", 600, 800};
    gOptions.clearColor = {12.0f, 50.0f, 100.0f, 255.0f};
    // Check if args override
    if(Util::doesParamExist(const_cast<char*>("-width"), argv, args)){
        try { gOptions.w = std::stoi(Util::getParam(const_cast<char*>("-width"), argv, args)); }
        catch (std::invalid_argument e) { 
            Util::Log("main", "Invalid argument to -width!\n");
            return -1;
        }
    }
    if(Util::doesParamExist(const_cast<char*>("-height"), argv, args)){
        try { gOptions.h = std::stoi(Util::getParam(const_cast<char*>("-height"), argv, args)); }
        catch (std::invalid_argument e) { 
            Util::Log("main", "Invalid argument to -height!\n");
            return -1;
        }
    }
    // Create graphics engine
    graphicsEngine = std::make_unique<Rendering::GraphicsEngine>(gOptions);

    // Create test terrain
    TerrainObject terrainObject;
    
    // Triangle
    TestObject tObject;

    // Create camera
    std::shared_ptr<Rendering::Camera> camera = Rendering::Camera::create();

    // Create scene
    Rendering::Scene scene;
    scene.addDrawable(terrainObject.getDrawable());
    scene.addDrawable(tObject.getDrawable());

    

    // TODO: Make this loop timer based 
    while(1){
        if(graphicsEngine->tick(scene, *camera) < 0) break;
    }

    return 0;
}
