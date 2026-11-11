/*
    Project Corrode Graphics Engine (PCGE)
    camera.hpp
*/

#pragma once

#include <memory>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace glm;


namespace Rendering {
    class CameraController;

    struct CameraMats {
		alignas(16) mat4 view;
		alignas(16) mat4 projection;
	};

    struct CameraData {
        vec3 position;
        vec3 forward;
        vec3 up = vec3(0.0f, 1.0f, 0.0f);

        float fov = radians(45.0f);
        float aspectRatio;
        float near = 0.1f;
        float far = 1000.0f;
    };


    class Camera : public std::enable_shared_from_this<Camera> {
        private: 
            CameraData data;
            CameraMats mats;

        private:
            void updateViewMat();
            void updateProjectionMat();

        public: 
            std::unique_ptr<CameraController> control;

        public:
            Camera();
            void init(); // "true" constructor
            ~Camera();
            void setPosition(vec3 position);
            void setForward(vec3 forward);
            void setPerspective(float fov, float aspectRatio, float near, float far);

            mat4 inline getView() { return mats.view; }
            mat4 inline getProjection() { return mats.projection; }
            vec3 inline getPosition() { return data.position; }
            vec3 inline getForward() { return data.forward; }

            static std::shared_ptr<Camera> create(){
                std::shared_ptr<Camera> cam = std::shared_ptr<Camera>(new Camera());
                cam->init();
                return cam;
            }
    };

    class CameraController {
        public:
            float orbitSensitivity = 0.2f;
            float zoomSensitivity = 0.0025f;

        private:
            std::shared_ptr<Camera> camera;

            bool firstMouse;
            float lastMouseX;
            float lastMouseY;

            float distance;
            float pitch;
            float yaw;
        public:
            CameraController(std::shared_ptr<Camera> camera);
            void handleInput(GLFWwindow *window);
    };
}
