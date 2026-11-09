/*
    Project Corrode
    object.hpp - Class for an object in the world
*/
#pragma once
// STD includes
#include <memory>
// Corrode includes
#include <common/transform.hpp>
#include <graphics/include/drawable.hpp>

class Object{
protected:
    // Drawable
    std::shared_ptr<Rendering::Drawable> drawable;
public:
    Object();

    // 
    virtual void tick() = 0;

    // Getter
    std::shared_ptr<Rendering::Drawable> getDrawable() { return drawable; }
};