/*
    Project Corrode Graphics Engine (PCGE)
    scene.hpp - Holds drawables for the graphics engine to call their 'draw' functions on a tick
*/
#pragma once
// C++
#include <vector>
#include <memory>
//
#include <drawable.hpp>

namespace Rendering{
    class Scene{
    private:
        std::vector<std::shared_ptr<Drawable>> list;
    public:
        Scene();

        void addDrawable(std::shared_ptr<Drawable> obj);

        // Getters
        std::vector<std::shared_ptr<Drawable>> getObjects() { return list; }
    };
}