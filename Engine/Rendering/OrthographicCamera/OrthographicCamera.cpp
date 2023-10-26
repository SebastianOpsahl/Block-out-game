#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(const Frustrum& frustrum, const glm::vec3& position, float rotation) {
    SetFrustrum(frustrum);
    SetPosition(position);
    SetRotation(rotation);
}

void OrthographicCamera::RecalculateMatrix() {
    ProjectionMatrix = glm::ortho(CameraFrustrum.left, CameraFrustrum.right, CameraFrustrum.bottom,
        CameraFrustrum.top, CameraFrustrum.near, CameraFrustrum.far);
    glm::vec3 rotated = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(Position, 1.0f));
    ViewMatrix = glm::lookAt(rotated, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}