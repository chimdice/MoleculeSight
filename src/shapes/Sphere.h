#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Mesh.h"

class Sphere : public Mesh
{
    private:
        float radius {};
        float numSectors {};
        float numStacks {};
        float pi {3.141529};
    
        void buildVertices();
        void generateTriangles();

    public:
        Sphere(float radius, float numSectors, float numStacks, int instances);
        void draw();

};

#endif