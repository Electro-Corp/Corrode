/*
    Project Corrode Graphics Engine (PCGE)
    And there was light.cpp
*/
#include <light.hpp>

namespace Rendering{

Light::Light(glm::vec3 c, glm::vec3 a, glm::vec3 s, glm::vec3 d, glm::vec3 p) 
    : color(c), ambient(a), specular(s), diffuse(d), position(p){

}

};