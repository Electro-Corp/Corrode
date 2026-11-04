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
private:
    std::unique_ptr<Rendering::Drawable> drawable;
public:
    Object();
};