/*
    Project Corrode
    object.hpp - Extends Object to preform tests
*/

#include <core/objects/testObject.hpp>
#include <graphics/include/drawables/testTriangle.hpp>

TestObject::TestObject(){
    this->drawable = std::make_shared<Drawable::TestTriangle>();
}

void TestObject::tick(){
    drawable->draw();
}