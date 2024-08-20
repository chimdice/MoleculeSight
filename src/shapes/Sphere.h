#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Math3d.h"

class Sphere
{
    private:
        std::vector<Vector3f> vertices {};
        std::vector<Vector3f> normalizedVertices {};
        std::vector<float> sphereTriangles {};
        std::vector<float> sphereTrianglesColor {};

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

        std::vector<float> getTriangles ()
        {
            return sphereTriangles;
        }

        std::vector<float> getColor ()
        {
            return sphereTrianglesColor;
        }

        int getNumTriangles ()
        {
            return numTriangles;
        }



};

#endif