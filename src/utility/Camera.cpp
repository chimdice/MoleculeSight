#include "Camera.h"

Camera::Camera(Vector3f inPosition, float fov, float near, float far, float width, float height)
{
    this->fov=fov;
    this->aspectRatio=width/height;
    this->near=near;
    this->far=far;
    this->width=width;
    this->height=height;

    this->position=inPosition;
    Vector3f cD {position.x + orientation.x, position.y + orientation.y, position.z + orientation.z};
    this->cameraDirection = NormalizeVector(cD);

    Vector3f cR {crossProduct(up, cameraDirection)};
    this->cameraRight = NormalizeVector(cR);

    Vector3f cU {crossProduct(cameraDirection, cameraRight)};
    this->cameraUp = NormalizeVector(cU);
}

void Camera::Init ()
{
    Vector3f cD {position.x + orientation.x, position.y + orientation.y, position.z + orientation.z};
    cameraDirection = NormalizeVector(cD);

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
    //std::cout << "x is " << position.x << ",y is " << position.y << " and z is "<< position.z<<". \n";

    //Init();
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
    //projTransform.createPerspective(90.0f, 800.0f/600.0f, 1.0f, 100.0f);
    projTransform.createOrtho(orienfov*aspectRatio, orienfov, near, far);
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

void Camera::rotate (float yaw, float pitch)
{
    float yawRad {yaw * (3.14159265359/180)};
    float pitchRad {pitch * (3.14159265359/180)};
    Vector3f direction {};
    direction.x = std::cos(yawRad) * std::cos(pitchRad);
    direction.y = std::sin(pitchRad);
    direction.z = std::sin(yawRad) * std::cos(pitchRad);
    Vector3f normDir = NormalizeVector(direction);
    orientation.x = normDir.x;
    orientation.y = normDir.y;
    orientation.z = normDir.z;
    //std::cout << "x is " << orientation.x << ",y is " << orientation.y << " and z is "<< orientation.z<<". \n";
    Init();
}

