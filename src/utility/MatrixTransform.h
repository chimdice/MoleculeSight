#ifndef MATRIXT_H
#define MATRIXT_H

#include <iostream>
#include <cmath>
#include "../Math3d.h"

class MatrixTransform
{
    private:
        Matrix4 currentMatrix {};
    
    public:
        MatrixTransform(Matrix4 matrix);
        void translate(Vector3f vector);
        void scale(Vector3f vector);
        void rotate(Vector3f vector, float angle);
        void createPerspective(float fov, float aspectRation, float front, float back);
        void createOrtho(float height, float width, float near, float far);
        void print();
        void fillArray(float array[16]);
        Matrix4 getMatrix();

    
};

#endif