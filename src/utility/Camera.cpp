#include "Camera.h"

Camera::Camera(Vector3f inPosition, float fov, float aspectRatio, float near, float far)
{
    this->fov=fov;
    this->aspectRatio=aspectRatio;
    this->near=near;
    this->far=far;

    this->position=inPosition;
    Vector3f cD {position.x + orientation.x, position.y + orientation.y, position.z + orientation.z};
    this->cameraDirection = NormalizeVector(cD);

    Vector3f cR {crossProduct(up, cameraDirection)};
    this->cameraRight = NormalizeVector(cR);

    Vector3f cU {crossProduct(cameraDirection, cameraRight)};
    this->cameraUp = NormalizeVector(cU);
}


void Camera::updatePosition (Vector3f inPosition)
{
    position.x = inPosition.x;
    position.y = inPosition.y;
    position.z = inPosition.z;
}

void Camera::addShader(unsigned int shaderProgramIn)
{
    shaderProgram = shaderProgramIn;
}

void Camera::view()
{
    //view matrix
    Matrix4 posMatrix {1.0f};
    posMatrix.matrix[12] = -position.x;
    posMatrix.matrix[13] = -position.y;
    posMatrix.matrix[14] = -position.z;

    Matrix4 lookAtMatrix {1.0f};
    lookAtMatrix.matrix[0] = cameraRight.x;
    lookAtMatrix.matrix[4] = cameraRight.y;
    lookAtMatrix.matrix[8] = cameraRight.z;
    lookAtMatrix.matrix[1] = cameraUp.x;
    lookAtMatrix.matrix[5] = cameraUp.y;
    lookAtMatrix.matrix[9] = cameraUp.z;
    lookAtMatrix.matrix[2] = cameraDirection.x;
    lookAtMatrix.matrix[6] = cameraDirection.y;
    lookAtMatrix.matrix[10] = cameraDirection.z;
    Matrix4 view {Multiply4x4(lookAtMatrix.matrix,posMatrix.matrix)};

    //projection matrix
    Matrix4 proj {1.0f};
    MatrixTransform projTransform {proj};
    projTransform.createProjection(90.0f, 800.0f/600.0f, 1.0f, 100.0f);
    Matrix4 newProj = projTransform.getMatrix();

    Matrix4 camera {Multiply4x4(newProj.matrix, view.matrix)};

    int projLocation {glGetUniformLocation(shaderProgram, "camera")};
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, &camera.matrix[0]);
}

Vector3f Camera::shiftSide ()
{
    Vector3f side {crossProduct(orientation, up)};
    return NormalizeVector(side);
}
