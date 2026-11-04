/*
    Project Corrode
    drawable.hpp - Class for things that can be drawn
*/
#pragma once

namespace Rendering {
    class Drawable{
    private:
    public:
        Drawable();

        // Abstract function for child classes
        virtual void draw() = 0;
    };
} // Rendering