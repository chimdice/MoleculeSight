#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "../Math3d.h"
#include "../utility/utility.h"

class Sphere
{
    private:
        std::vector<Vector4f> vertices {};
        std::vector<Vector4f> normalizedVertices {};
        std::vector<float> vertexVector {};
        std::vector<float> sphereTrianglesColor {};
        std::vector<int> vertexIndex {};

        float radius {};
        float numSectors {};
        float numStacks {};
        float pi {3.141529};
        int numTriangles {0};
    
        void buildVertices();
        void generateTriangles();

    public:
        Sphere(float radius, float numSectors, float numStacks);
        void draw();

        std::vector<float> getVertex ()
        {
            return vertexVector;
        }

        std::vector<float> getColor ()
        {
            return sphereTrianglesColor;
        }

        std::vector<int> getVertexIndex ()
        {
            return vertexIndex;
        }

        int getNumTriangles ()
        {
            return numTriangles;
        }



};

#endif