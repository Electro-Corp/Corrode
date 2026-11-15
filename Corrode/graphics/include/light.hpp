/*
    Project Corrode Graphics Engine (PCGE)
    And corrode said, let there be light.hpp
*/
#pragma once

// glm
#include <glm/glm.hpp>

namespace Rendering{
    class Light{
    private:
    public:
        glm::vec3 color, specular, diffuse;

        Light(glm::vec3 color, glm::vec3 specular, glm::vec3 diffuse);
    };
}