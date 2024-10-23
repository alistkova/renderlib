#include "scene/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : _position(glm::vec3(0.0f, 0.0f, 3.0f)),
      _rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
      _fov(45.0f),
      _width(800.0f),
      _height(600.0f),
      _direction(glm::vec3(0.0f, 0.0f, -1.0f)),
      _viewMatrix(glm::mat4(1.0f)) {}

Camera::Camera(const glm::vec3& position, float fov, float width, float height)
    : _position(position),
      _rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
      _fov(fov),
      _width(width),
      _height(height),
      _direction(glm::vec3(0.0f, 0.0f, -1.0f)),
      _viewMatrix(glm::mat4(1.0f)) {}

glm::mat4 Camera::getViewMatrix() const {
    return _viewMatrix;
}

void Camera::updateViewMatrix() {
    _viewMatrix = glm::lookAt(_position, _position + _direction,
                              glm::vec3(0.0f, 1.0f, 0.0f));
}