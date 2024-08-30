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
        Vector3f look {0,0,0};
        Vector3f pivot {0, 0, 1};
        Vector3f cameraDirection {};
        Vector3f cameraRight {};
        Vector3f cameraUp {};

        int width {};
        int height {};
        float speed {0.1};
        float sensitivity {0.1};
        float orienfov {10};
        float yaw {0.0f};
        float pitch {0.0f};

        float fov {};
        float aspectRatio {};
        float near {};
        float far {};
        unsigned int shaderProgram {};
        unsigned int light {};



    public:
        Camera (Vector3f inPosition, float fov, float near, float far, float width, float height);
        void updatePosition (unsigned char key);
        void addShader(unsigned int shaderProgram, unsigned int light);
        void view ();
        void rotate (float yawIn, float pitchIn);
        void Init (int status);
        Vector3f shiftSide ();

        float getSpeed ()
        {
            return speed;
        }

        Vector3f getOrientation ()
        {
            return orientation;
        }

        void updateOfov (int but)
        {
            if (but == 3) {
                orienfov += sensitivity;
            } else {
                orienfov -= sensitivity;
            }
            
        }

        void updatePivot(Vector3f piv)
        {
            pivot.x = piv.x;
            pivot.y = piv.y;
            pivot.z = piv.z;
        }

};

#endif