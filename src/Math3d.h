#ifndef MATH_H
#define MATH_H

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
        std::cout << " " << matrix[0]<< " " << matrix[1]<< " "<< matrix[2]<< " "<< matrix[3]<< "\n";
        std::cout << " " << matrix[4]<< " " << matrix[5]<< " "<< matrix[6]<< " "<< matrix[7]<< "\n";
        std::cout << " " << matrix[8]<< " " << matrix[9]<< " "<< matrix[10]<< " "<< matrix[11]<< "\n";
        std::cout << " " << matrix[12]<< " " << matrix[13]<< " "<< matrix[14]<< " "<< matrix[15]<< "\n";
        std::cout << '\n';
    }

    void multiply(float matrix2[16])
    {
        Matrix4 tempMatrix {};
        //row 1
        tempMatrix.matrix[0] = matrix[0]*matrix2[0] + matrix[1]*matrix2[4] + matrix[2]*matrix2[8]+ matrix[3]*matrix2[12];
        tempMatrix.matrix[1] = matrix[0]*matrix2[1] + matrix[1]*matrix2[5] + matrix[2]*matrix2[9]+ matrix[3]*matrix2[13];
        tempMatrix.matrix[2] = matrix[0]*matrix2[2] + matrix[1]*matrix2[6] + matrix[2]*matrix2[10]+ matrix[3]*matrix2[14];
        tempMatrix.matrix[3] = matrix[0]*matrix2[3] + matrix[1]*matrix2[7] + matrix[2]*matrix2[11]+ matrix[3]*matrix2[15];

        //row 2
        tempMatrix.matrix[4] = matrix[4]*matrix2[0] + matrix[5]*matrix2[4] + matrix[6]*matrix2[8]+ matrix[7]*matrix2[12];
        tempMatrix.matrix[5] = matrix[4]*matrix2[1] + matrix[5]*matrix2[5] + matrix[6]*matrix2[9]+ matrix[7]*matrix2[13];
        tempMatrix.matrix[6] = matrix[4]*matrix2[2] + matrix[5]*matrix2[6] + matrix[6]*matrix2[10]+ matrix[7]*matrix2[14];
        tempMatrix.matrix[7] = matrix[4]*matrix2[3] + matrix[5]*matrix2[7] + matrix[6]*matrix2[11]+ matrix[7]*matrix2[15];

        //row 3
        tempMatrix.matrix[8] = matrix[8]*matrix2[0] + matrix[9]*matrix2[4] + matrix[10]*matrix2[8]+ matrix[11]*matrix2[12];
        tempMatrix.matrix[9] = matrix[8]*matrix2[1] + matrix[9]*matrix2[5] + matrix[10]*matrix2[9]+ matrix[11]*matrix2[13];
        tempMatrix.matrix[10] = matrix[8]*matrix2[2] + matrix[9]*matrix2[6] + matrix[10]*matrix2[10]+ matrix[11]*matrix2[14];
        tempMatrix.matrix[11] = matrix[8]*matrix2[3] + matrix[9]*matrix2[7] + matrix[10]*matrix2[11]+ matrix[11]*matrix2[15];

        //row 4
        tempMatrix.matrix[12] = matrix[12]*matrix2[0] + matrix[13]*matrix2[4] + matrix[14]*matrix2[8]+ matrix[15]*matrix2[12];
        tempMatrix.matrix[13] = matrix[12]*matrix2[1] + matrix[13]*matrix2[5] + matrix[14]*matrix2[9]+ matrix[15]*matrix2[13];
        tempMatrix.matrix[14] = matrix[12]*matrix2[2] + matrix[13]*matrix2[6] + matrix[14]*matrix2[10]+ matrix[15]*matrix2[14];
        tempMatrix.matrix[15] = matrix[12]*matrix2[3] + matrix[13]*matrix2[7] + matrix[14]*matrix2[11]+ matrix[15]*matrix2[15];

        for (int i = 0; i < 16; i++) {
            matrix[i] = tempMatrix.matrix[i];
        }
    };
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

#endif