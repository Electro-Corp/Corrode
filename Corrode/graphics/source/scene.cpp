/*
    Project Corrode Graphics Engine (PCGE)
    scene.hpp - Holds drawables for the graphics engine to call their 'draw' functions on a tick
*/
#include <scene.hpp>

namespace Rendering{

Scene::Scene(){

}


void Scene::addDrawable(std::shared_ptr<Drawable> obj){
    this->list.push_back(obj);
}


}