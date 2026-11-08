#include "Camera.hpp"

Rendering::Camera::Camera() {
    control = new CameraController(this);
    updateViewMat();
    updateProjectionMat();
}

Rendering::Camera::~Camera() {
    delete control;
}

void Rendering::Camera::setPosition(vec3 position) {
    this->data.position = position;
    updateViewMat();
}

void Rendering::Camera::setForward(vec3 forward) {
    this->data.forward = forward;
    updateViewMat();
}

void Rendering::Camera::setPerspective(float fov, float aspectRatio, float near, float far) {
    this->data.fov = fov;
    this->data.aspectRatio = aspectRatio;
    this->data.near = near;
    this->data.far = far;
    updateProjectionMat();
}

void Rendering::Camera::updateViewMat() {
   this->mats.view = lookAt(data.position, data.forward, data.up); 
}

void Rendering::Camera::updateProjectionMat() {
    this->mats.projection = perspective(data.fov, data.aspectRatio, data.near, data.far);
    this->mats.projection[1][1] *= -1;
}

Rendering::CameraController::CameraController(Rendering::Camera* camera) {
    this->camera = camera;
    firstMouse = true;
    distance = 1.0f;
    pitch = 0.0f;
    yaw = 180.0f;
}

void Rendering::CameraController::handleInput(GLFWwindow *window) {
    // TODO: Make this function move camera based on mouse??? this whole class will probably need changing
}
