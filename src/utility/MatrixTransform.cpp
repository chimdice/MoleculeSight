#include "MatrixTransform.h"

MatrixTransform::MatrixTransform(Matrix4 matrix)
{
    this->currentMatrix=matrix;
}

void MatrixTransform::translate(Vector3f vector)
{
   Matrix4 translate {1};
   translate.matrix[3] = vector.x;
   translate.matrix[7] = vector.y;
   translate.matrix[11] = vector.z;

   currentMatrix.multiply(translate.matrix);
}

void MatrixTransform::scale(Vector3f vector)
{
   Matrix4 scale {1};
   scale.matrix[0] = vector.x;
   scale.matrix[5] = vector.y;
   scale.matrix[10] = vector.z;

   currentMatrix.multiply(scale.matrix);
}

void MatrixTransform::rotate(Vector3f vector, float angle)
{

    float radAngle {angle * (3.14159265359/180)};
    float length {std::sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z)};

    float rX {vector.x/length};
    float rY {vector.y/length};
    float rZ {vector.z/length};

    float cosAngle {std::cos(radAngle)};
    float sinAngle {std::sin(radAngle)};
    float minusCosAngle {1 - cosAngle};

    Matrix4 rotate {1};
    rotate.matrix[0] = cosAngle + rX*rX*minusCosAngle;
    rotate.matrix[1] = minusCosAngle*rY*rX - sinAngle*rZ;
    rotate.matrix[2] = minusCosAngle*rZ*rX + sinAngle*rY;

    rotate.matrix[4] = minusCosAngle*rY*rX + sinAngle*rZ;
    rotate.matrix[5] = cosAngle + rY*rY*minusCosAngle;
    rotate.matrix[6] = minusCosAngle*rY*rZ - sinAngle*rX;

    rotate.matrix[8] = minusCosAngle*rZ*rX - sinAngle*rY;
    rotate.matrix[9] = minusCosAngle*rY*rZ + sinAngle*rX;
    rotate.matrix[10] = cosAngle + rZ*rZ*minusCosAngle;

    rotate.print();

    currentMatrix.multiply(rotate.matrix);
}

void MatrixTransform::print()
{
    currentMatrix.print();
}

void MatrixTransform::fillArray(float inMatrix[16])
{
    for (int i = 0; i < 16; i++) {
            inMatrix[i] = currentMatrix.matrix[i];
        }
}