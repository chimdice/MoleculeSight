#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../Math3d.h"

class Camera
{
    private:
        Vector3f position {};
        Vector3f orientation {0, 0 , -1};
        Vector3f up {0, 1, 0};

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
        Camera (Vector3f position, float fov, float aspectRatio, float near, float far);
        void addShader(unsigned int shaderProgram);
        void view ();
        void wPress();


};

#endif