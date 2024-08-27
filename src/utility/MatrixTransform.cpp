#include "MatrixTransform.h"

MatrixTransform::MatrixTransform(Matrix4 matrix)
{
    this->currentMatrix=matrix;
}

void MatrixTransform::translate(Vector3f vector)
{
   Matrix4 translate {1};
   translate.matrix[12] = vector.x;
   translate.matrix[13] = vector.y;
   translate.matrix[14] = vector.z;

   Matrix4 newMatrix {Multiply4x4(currentMatrix.matrix, translate.matrix)};
   currentMatrix.updateMatrix(newMatrix.matrix);
}

void MatrixTransform::scale(Vector3f vector)
{
   Matrix4 scale {1};
   scale.matrix[0] = vector.x;
   scale.matrix[5] = vector.y;
   scale.matrix[10] = vector.z;

   Matrix4 newMatrix {Multiply4x4(currentMatrix.matrix, scale.matrix)};
   currentMatrix.updateMatrix(newMatrix.matrix);
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
    rotate.matrix[4] = minusCosAngle*rY*rX - sinAngle*rZ;
    rotate.matrix[8] = minusCosAngle*rZ*rX + sinAngle*rY;

    rotate.matrix[1] = minusCosAngle*rY*rX + sinAngle*rZ;
    rotate.matrix[5] = cosAngle + rY*rY*minusCosAngle;
    rotate.matrix[9] = minusCosAngle*rY*rZ - sinAngle*rX;

    rotate.matrix[2] = minusCosAngle*rZ*rX - sinAngle*rY;
    rotate.matrix[6] = minusCosAngle*rY*rZ + sinAngle*rX;
    rotate.matrix[10] = cosAngle + rZ*rZ*minusCosAngle;

    Matrix4 newMatrix {Multiply4x4(currentMatrix.matrix, rotate.matrix)};
    currentMatrix.updateMatrix(newMatrix.matrix);
}

void MatrixTransform::createProjection(float fov, float aspectRatio, float near, float far)
{
    float fovRad {(fov/2) * (3.14159265359/180)};
    float tangent {std::tan(fovRad)};
    float scaleFactor {1/tangent};
    float zRange {far - near};

    //std::cout << "The aspect ratio is " << aspectRatio << ". \n";


    Matrix4 projection(1);
    // projection.matrix[0] = (2*near) / (right - left);
    // projection.matrix[2] = (right + left) / (right - left);
    // projection.matrix[5] = (2*near) / (top - bottom);
    // projection.matrix[6] = (top + bottom) / (top - bottom);
    // projection.matrix[10] = -(far+near) / (far- near);
    // projection.matrix[11] = -(2*far*near) / (far - near);
    // projection.matrix[14] = -1;

    projection.matrix[0] = scaleFactor*(1/aspectRatio);
    projection.matrix[5] = scaleFactor;
    projection.matrix[10] = far / zRange;
    projection.matrix[14] = ((near*far)/(zRange));
    projection.matrix[11] = -1;
    projection.matrix[15] = 0;

    // projection.matrix[0] = scaleFactor*(1/aspectRatio);
    // projection.matrix[5] = scaleFactor;
    // projection.matrix[10] = -far / zRange;
    // projection.matrix[14] = -((near*far)/(zRange));
    // projection.matrix[11] = -1;
    // projection.matrix[15] = 0;

    Matrix4 newMatrix {Multiply4x4(currentMatrix.matrix, projection.matrix)};
    currentMatrix.updateMatrix(newMatrix.matrix);
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

Matrix4 MatrixTransform::getMatrix()
{
    return currentMatrix;
}