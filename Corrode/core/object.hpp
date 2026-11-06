/*
    Project Corrode
    object.hpp - Class for an object in the world
*/
#pragma once
// STD includes
#include <memory>
// Corrode includes
#include <graphics/include/drawable.hpp>

class Object{
protected:
    std::shared_ptr<Rendering::Drawable> drawable;
public:
    Object();

    // 
    virtual void tick() { drawable->draw(); }; 

    // Getter
    std::shared_ptr<Rendering::Drawable> getDrawable() { return drawable; }
};