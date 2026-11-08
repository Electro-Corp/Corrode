#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

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


    class Camera {
        private: 
            CameraData data;
            CameraMats mats;

        private:
            void updateViewMat();
            void updateProjectionMat();

        public: 
            CameraController *control;

        public:
            Camera();
            ~Camera();
            void setPosition(vec3 position);
            void setForward(vec3 forward);
            void setPerspective(float fov, float aspectRatio, float near, float far);

            mat4 inline getView() { return mats.view; }
            mat4 inline getProjection() { return mats.projection; }
            vec3 inline getPosition() { return data.position; }
            vec3 inline getForward() { return data.forward; }
    };

    class CameraController {
        public:
            float orbitSensitivity = 0.2f;
            float zoomSensitivity = 0.0025f;

        private:
            Camera *camera;

            bool firstMouse;
            float lastMouseX;
            float lastMouseY;

            float distance;
            float pitch;
            float yaw;
        public:
            CameraController(Camera *camera);
            void handleInput(GLFWwindow *window);
    };
}
