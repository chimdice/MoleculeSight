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

    public:
        Camera (Vector3f position);
        void Matrix ();
        //void Inputs ();
};

#endif