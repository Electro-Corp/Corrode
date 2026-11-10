/*
    Project Corrode
    object.hpp - Extends Object to preform tests
*/

#include <core/objects/test_object.hpp>
#include <graphics/include/drawables/test_triangle.hpp>

TestObject::TestObject(){
    this->drawable = std::make_shared<Drawable::TestTriangle>();
}

void TestObject::tick(){
    
}