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

void MatrixTransform::print()
{
    currentMatrix.print();
}