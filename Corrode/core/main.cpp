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
#include <graphics/include/light.hpp>
// Objects
#include <core/objects/test_object.hpp>
#include <core/objects/terrain_object.hpp>
#include <core/objects/basic_creature.hpp>
// Simulation
#include <sim/include/world.hpp>

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

#define MAP_SIZE 256
#define JITS 256

// Global pointer for the graphics engine
std::unique_ptr<Rendering::GraphicsEngine> graphicsEngine;

int main(int argv, char* args[]){
    // Generate settings
    Rendering::EngineInitOptions gOptions = {"Corrode", 600, 800, 1024 * ((MAP_SIZE) / 256), MAP_SIZE};
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
    if(Util::doesParamExist(const_cast<char*>("-noshadows"), argv, args)){
        gOptions.shadowSize = 0;
    }
    // Create graphics engine
    graphicsEngine = std::make_unique<Rendering::GraphicsEngine>(gOptions);

    // Create test terrain
    TerrainObject terrainObject(MAP_SIZE);
    // Test creature
    BasicCreature creature(glm::vec3(100.0f, 50.0f, 100.0f));
    creature.transform.Scale(glm::vec3(2.0f, 2.0f, 2.0f));

    // Create jits
    std::vector<BasicCreature> creatures;
    for(int i = 0; i < JITS; i++){
        BasicCreature tmp(glm::vec3((rand() / 32767.0) * (MAP_SIZE), 50.0f, (rand() / 32767.0) * (MAP_SIZE)));
        tmp.transform.Scale(glm::vec3(2.0f, 2.0f, 2.0f));
        creatures.push_back(tmp);
    }

    // Create camera
    std::shared_ptr<Rendering::Camera> camera = Rendering::Camera::create();
    camera->setPerspective(glm::radians(45.0), (float) gOptions.w / gOptions.h, 0.1f, 2500.0f);
    camera->setPosition(glm::vec3(128.0f, 340.0f, 380.0f));
    camera->setForward(glm::normalize(glm::vec3(0.0f, -300.0f, -252.0f)));
    camera->control->attachWindow(graphicsEngine->getWindow(), &(graphicsEngine->userPointers));

    // Lighting
    Rendering::Light sun(
        glm::vec3(1.0, 1.0, 1.0), // color
        glm::vec3(1.0, 1.0, 1.0), // ambient
        glm::vec3(1.0, 1.0, 1.0), // specular
        glm::vec3(1.0, 1.0, 1.0), // diffuse
        glm::vec3(MAP_SIZE + 250.0f, 350.0f,  MAP_SIZE + 250.0f) // position
    );

    // Create scene
    Rendering::Scene scene;
    scene.addDrawable(terrainObject.getDrawable());
    scene.addDrawable(creature.getDrawable());

    // Create world
    Simulation::World world;
    world.terrain = terrainObject.getTerrain();
    // Add creature
    world.addEntity(creature.getEntity());

    // Add all the creatures
    for(int i = 0; i < creatures.size(); i++){
        scene.addDrawable(creatures[i].getDrawable());
        world.addEntity(creatures[i].getEntity());
    }

    // TODO: Make this loop timer based 
    while(1){
        // TODO: Make some way for this to be in a "scene" like thing
        // but still keep Rendering::Scene completely isolated 
        creature.tick();
        for(int i = 0; i < creatures.size(); i++) creatures[i].tick();
        // Tick World
        world.tick();
        // Tick Graphics Engine
        if(graphicsEngine->tick(scene, *camera, sun) < 0) break;
    }

    return 0;
}
