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
        glm::vec3 color, ambient, specular, diffuse, position;

        Light(glm::vec3 color, glm::vec3 ambient, glm::vec3 specular, glm::vec3 diffuse, glm::vec3 position);
    };
}