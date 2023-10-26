#include <glm/gtc/matrix_transform.hpp>

#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(const Frustrum& frustrum, const glm::vec3& position,
	const glm::vec3& lookAt, const glm::vec3& upVector) {

	SetFrustrum(frustrum);
	SetPosition(position);
	SetLookAt(lookAt);
	SetUpVector(upVector);
}

void PerspectiveCamera::RecalculateMatrix() {
	ProjectionMatrix = glm::perspective(
		CameraFrustrum.angle, CameraFrustrum.width / CameraFrustrum.height,
		CameraFrustrum.near, CameraFrustrum.far
	);
	ViewMatrix = glm::lookAt(Position, LookAt, UpVector);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}