/*
    Project Corrode
    test_object.hpp - Extends Object to preform tests
*/
#include <core/object.hpp>

class TestObject : public Object {
public:
    TestObject();

    void tick() override;
};