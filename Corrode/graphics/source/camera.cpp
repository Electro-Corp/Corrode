/*
    Project Corrode Graphics Engine (PCGE)
    camera.hpp
*/

#include <Camera.hpp>

namespace Rendering{

Camera::Camera() {
    updateViewMat();
    updateProjectionMat();
}

void Camera::init(){
    control = std::make_unique<CameraController>(this->shared_from_this());
}

Camera::~Camera() {
    
}

void Camera::setPosition(vec3 position) {
    this->data.position = position;
    updateViewMat();
}

void Camera::setForward(vec3 forward) {
    this->data.forward = forward;
    updateViewMat();
}

void Camera::setPerspective(float fov, float aspectRatio, float near, float far) {
    this->data.fov = fov;
    this->data.aspectRatio = aspectRatio;
    this->data.near = near;
    this->data.far = far;
    updateProjectionMat();
}

void Camera::updateViewMat() {
   this->mats.view = lookAt(data.position, data.position + data.forward, data.up); 
}

void Camera::updateProjectionMat() {
    this->mats.projection = perspective(data.fov, data.aspectRatio, data.near, data.far);
    //this->mats.projection[1][1] *= -1;
}

CameraController::CameraController(std::shared_ptr<Camera> camera) {
    this->camera.swap(camera);
    firstMouse = true;
    distance = 1.0f;
    pitch = 0.0f;
    yaw = 180.0f;
}

void CameraController::handleInput(GLFWwindow *window) {
    // TODO: Make this function move camera based on mouse??? this whole class will probably need changing
}

}