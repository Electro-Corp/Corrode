/*
    Project Corrode Graphics Engine (PCGE)
    camera.hpp
*/

#include <camera.hpp>
#include <graphics.hpp>

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
    this->data.forward = normalize(forward);
    updateViewMat();
}

void Camera::move(vec3 offset) {
    data.position += offset;
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

void CameraController::attachWindow(GLFWwindow* window, UserPointers* pointers) {
    syncOrientation();
    pointers->camera = this;
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraController::handleInput(GLFWwindow *window, float deltaTime) {
    const vec3 forward = normalize(vec3(camera->getForward().x, 0.0f, camera->getForward().z));
    const vec3 right = normalize(cross(forward, vec3(0.0f, 1.0f, 0.0f)));
    const vec3 up = normalize(cross(forward, right));

    const float distance = movementSpeed * deltaTime;
    vec3 movement(0.0f);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movement += forward;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movement -= forward;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movement += right;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movement -= right;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) movement += up;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) movement -= up;

    if(length(movement) > 0.0f) {
        camera->move(normalize(movement) * distance);
    }
}

void CameraController::mouseCallback(GLFWwindow* window, double x, double y) {
    CameraController* controller = static_cast<UserPointers*>(glfwGetWindowUserPointer(window))->camera;
    if(controller != nullptr) controller->handleMouse(x, y);
}

void CameraController::handleMouse(double x, double y) {
    if(firstMouse) {
        lastMouseX = static_cast<float>(x);
        lastMouseY = static_cast<float>(y);
        firstMouse = false;
        return;
    }

    const float xOffset = (static_cast<float>(x) - lastMouseX) * mouseSensitivity;
    const float yOffset = (lastMouseY - static_cast<float>(y)) * mouseSensitivity;
    lastMouseX = static_cast<float>(x);
    lastMouseY = static_cast<float>(y);
    yaw += xOffset;
    pitch = clamp(pitch + yOffset, -maxPitch, maxPitch);

    const float yawRadians = radians(yaw);
    const float pitchRadians = radians(pitch);
    camera->setForward(normalize(vec3(
        cos(yawRadians) * cos(pitchRadians),
        sin(pitchRadians),
        sin(yawRadians) * cos(pitchRadians)
    )));
}

void CameraController::syncOrientation() {
    const vec3 forward = normalize(camera->getForward());
    pitch = degrees(asin(clamp(forward.y, -1.0f, 1.0f)));
    yaw = degrees(atan(forward.z, forward.x));
}

}
