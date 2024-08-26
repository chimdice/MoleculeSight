#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../Math3d.h"
#include "./MatrixTransform.cpp"

class Camera
{
    private:
        Vector3f position {};
        Vector3f orientation {0, 0 , -1};
        Vector3f up {0, 1, 0};
        Vector3f cameraDirection {};
        Vector3f cameraRight {};
        Vector3f cameraUp {};

        int width {};
        int height {};
        float speed {0.1};
        float sensitivity {100};

        float fov {};
        float aspectRatio {};
        float near {};
        float far {};
        unsigned int shaderProgram {};

    public:
        Camera (Vector3f inPosition, float fov, float aspectRatio, float near, float far);
        void updatePosition (Vector3f inPosition);
        void addShader(unsigned int shaderProgram);
        void view ();
        Vector3f shiftSide ();

        float getSpeed ()
        {
            return speed;
        }

        Vector3f getOrientation ()
        {
            return orientation;
        }

};

#endif