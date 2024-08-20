#include "Camera.h"

Camera::Camera(Vector3f position)
{
    this->position=position;
}

void Camera::Matrix()
{
    gluLookAt(
        position.x, position.y, position.z,
        position.x + orientation.x, position.y + orientation.y, position.z + orientation.z,
        0, 1, 0
    );
}