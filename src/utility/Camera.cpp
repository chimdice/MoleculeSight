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
    Vector3f cD {look.x - position.x, look.y - position.y, look.z - position.z};
    this->cameraDirection = NormalizeVector(cD);

    Vector3f cR {crossProduct(cameraDirection, up)};
    this->cameraRight = NormalizeVector(cR);

    Vector3f cU {crossProduct(cameraRight, cameraDirection)};
    this->cameraUp = NormalizeVector(cU);
}

void Camera::Init ()
{
    Vector3f cD {look.x - position.x, look.y - position.y, look.z - position.z};
    this->cameraDirection = NormalizeVector(cD);

    Vector3f cR {crossProduct(cameraDirection, up)};
    this->cameraRight = NormalizeVector(cR);

    Vector3f cU {crossProduct(cameraRight, cameraDirection)};
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
    lookAtMatrix.matrix[2] = -cameraDirection.x;
    lookAtMatrix.matrix[6] = -cameraDirection.y;
    lookAtMatrix.matrix[10] = -cameraDirection.z;
    Matrix4 view {Multiply4x4(lookAtMatrix.matrix,posMatrix.matrix)};
    // Matrix4 view {1.0f};
    // Vector3f rotateX {0,1,0};
    // MatrixTransform transfromView {view};
    // transfromView.rotate(rotateX, yaw);
    // transfromView.translate(position);
    // Matrix4 newView = transfromView.getMatrix();

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

void Camera::rotate (float yawIn, float pitchIn)
{

    // x rotation
    Matrix4 rotatex {1.0f};
    MatrixTransform xRotation {rotatex};
    xRotation.rotate(up, yawIn);
    Matrix4 finalXRotation = xRotation.getMatrix();
    Vector3f tempVec1 {position.x - pivot.x, position.y - pivot.y, position.z - pivot.z};
    Vector3f tempVec2 = Multiply4x1(finalXRotation.matrix, tempVec1);
    position.x = tempVec2.x;
    position.y = tempVec2.y;
    position.z = tempVec2.z;

    // y rotation
    Matrix4 rotatey {1.0f};
    MatrixTransform yRotation {rotatey};
    yRotation.rotate(cameraRight, pitchIn);
    Matrix4 finalYRotation = yRotation.getMatrix();
    Vector3f tempVec3 = Multiply4x1(finalYRotation.matrix, position);
    position.x = tempVec3.x;
    position.y = tempVec3.y;
    position.z = tempVec3.z;
    Init();


    // Vector3f direction {};
    // direction.x = std::cos(yawRad) * std::cos(pitchRad);
    // direction.y = std::sin(pitchRad);
    // direction.z = std::sin(yawRad) * std::cos(pitchRad);
    // Vector3f normDir = NormalizeVector(direction);
    // position.x =  orientation.x + normDir.x;
    // position.y =  orientation.y + normDir.y;
    // position.z =  orientation.z + normDir.z;
    //yaw = yawIn;
}

