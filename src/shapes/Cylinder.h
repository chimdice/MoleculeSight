#ifndef CYLINDER_H
#define CYLINDER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Mesh.h"

class Cylinder : public Mesh
{
    private:
        float radius {};
        float numSectors {};
        float pi {3.141529};
        float length {};
    
        void buildVertices();
        void generateTriangles();

    public:
        Cylinder(float radius, float length, float numSectors, int instances);
        void draw();

};

#endif