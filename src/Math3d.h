#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <cmath>

// class and structs

struct Vector3f
{
    float x {};
    float y {};
    float z {};

    Vector3f () {}

    Vector3f(float x, float y, float z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }

    Vector3f (float f)
    {
        this->x = f;
        this->y = f;
        this->z = f;
    }
    
};

struct Triangle
{
    Vector3f vertex1 {};
    Vector3f vertex2 {};
    Vector3f vertex3 {};

    Triangle(Vector3f vertex1, Vector3f vertex2, Vector3f vertex3)
    {
        this->vertex1=vertex1;
        this->vertex2=vertex2;
        this->vertex3=vertex3;
    }
};

struct Matrix4
{
    float matrix[16] {};

    Matrix4() {}

    Matrix4(float number)
    {
        for (int i = 0; i < 16; i++) {
            if ((i==0) || (i==5) || (i==10) || (i==15)) {
                matrix[i] = number;
            } else {
                matrix[i] = 0;
            }
        }
    }

    void print()
    {
        std::cout << '\n';
        std::cout << " " << matrix[0]<< " " << matrix[4]<< " "<< matrix[8]<< " "<< matrix[12]<< "\n";
        std::cout << " " << matrix[1]<< " " << matrix[5]<< " "<< matrix[9]<< " "<< matrix[13]<< "\n";
        std::cout << " " << matrix[2]<< " " << matrix[6]<< " "<< matrix[10]<< " "<< matrix[14]<< "\n";
        std::cout << " " << matrix[3]<< " " << matrix[7]<< " "<< matrix[11]<< " "<< matrix[15]<< "\n";
        std::cout << '\n';
    }

    void updateMatrix(float newMatrix[16])
    {
        for (int i = 0; i < 16; i++) {
            matrix[i] = newMatrix[i];
        }
    }
};

struct Vector4f
{
    float x {};
    float y {};
    float z {};
    float a {};

    Vector4f () {}

    Vector4f(float x, float y, float z, float a)
    {
        this->x=x;
        this->y=y;
        this->z=z;
        this->a=a;
    }

    Vector4f (float f)
    {
        this->x = f;
        this->y = f;
        this->z = f;
        this->a = a;
    }

};

//functions

Vector3f crossProduct(Vector3f v1, Vector3f v2)
{
    float newX {v1.y*v2.z - v1.z*v2.y};
    float newY {v1.z*v2.x - v1.x*v2.z};
    float newZ {v1.x*v2.y - v1.y*v2.x};

    Vector3f product(newX, newY, newZ);

    return product;
}

Vector3f NormalizeVector(Vector3f v)
{
    float l {std::sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z))};
    float nX {v.x/l};
    float nY {v.y/l};
    float nZ {v.z/l};

    Vector3f out {nX, nY, nZ};
    return out;
    
}

Matrix4 Multiply4x4(float matrix[16], float matrix2[16])
{
    Matrix4 tempMatrix {};
    //row 1
    tempMatrix.matrix[0] = matrix2[0]*matrix[0] + matrix2[1]*matrix[4] + matrix2[2]*matrix[8]+ matrix2[3]*matrix[12];
    tempMatrix.matrix[1] = matrix2[0]*matrix[1] + matrix2[1]*matrix[5] + matrix2[2]*matrix[9]+ matrix2[3]*matrix[13];
    tempMatrix.matrix[2] = matrix2[0]*matrix[2] + matrix2[1]*matrix[6] + matrix2[2]*matrix[10]+ matrix2[3]*matrix[14];
    tempMatrix.matrix[3] = matrix2[0]*matrix[3] + matrix2[1]*matrix[7] + matrix2[2]*matrix[11]+ matrix2[3]*matrix[15];

    //row 2
    tempMatrix.matrix[4] = matrix2[4]*matrix[0] + matrix2[5]*matrix[4] + matrix2[6]*matrix[8]+ matrix2[7]*matrix[12];
    tempMatrix.matrix[5] = matrix2[4]*matrix[1] + matrix2[5]*matrix[5] + matrix2[6]*matrix[9]+ matrix2[7]*matrix[13];
    tempMatrix.matrix[6] = matrix2[4]*matrix[2] + matrix2[5]*matrix[6] + matrix2[6]*matrix[10]+ matrix2[7]*matrix[14];
    tempMatrix.matrix[7] = matrix2[4]*matrix[3] + matrix2[5]*matrix[7] + matrix2[6]*matrix[11]+ matrix2[7]*matrix[15];

    //row 3
    tempMatrix.matrix[8] = matrix2[8]*matrix[0] + matrix2[9]*matrix[4] + matrix2[10]*matrix[8]+ matrix2[11]*matrix[12];
    tempMatrix.matrix[9] = matrix2[8]*matrix[1] + matrix2[9]*matrix[5] + matrix2[10]*matrix[9]+ matrix2[11]*matrix[13];
    tempMatrix.matrix[10] = matrix2[8]*matrix[2] + matrix2[9]*matrix[6] + matrix2[10]*matrix[10]+ matrix2[11]*matrix[14];
    tempMatrix.matrix[11] = matrix2[8]*matrix[3] + matrix2[9]*matrix[7] + matrix2[10]*matrix[11]+ matrix2[11]*matrix[15];

    //row 4
    tempMatrix.matrix[12] = matrix2[12]*matrix[0] + matrix2[13]*matrix[4] + matrix2[14]*matrix[8]+ matrix2[15]*matrix[12];
    tempMatrix.matrix[13] = matrix2[12]*matrix[1] + matrix2[13]*matrix[5] + matrix2[14]*matrix[9]+ matrix2[15]*matrix[13];
    tempMatrix.matrix[14] = matrix2[12]*matrix[2] + matrix2[13]*matrix[6] + matrix2[14]*matrix[10]+ matrix2[15]*matrix[14];
    tempMatrix.matrix[15] = matrix2[12]*matrix[3] + matrix2[13]*matrix[7] + matrix2[14]*matrix[11]+ matrix2[15]*matrix[15];

    return tempMatrix;

}

Vector3f Multiply4x1(float matrix[16], Vector3f vector)
{
    Vector3f tempVector {};

    tempVector.x = matrix[0]*vector.x + matrix[4]*vector.y + matrix[8]*vector.z;
    tempVector.y = matrix[1]*vector.x + matrix[5]*vector.y + matrix[9]*vector.z;
    tempVector.z = matrix[2]*vector.x + matrix[6]*vector.y + matrix[10]*vector.z;

    return tempVector;
}
#endif