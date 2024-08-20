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