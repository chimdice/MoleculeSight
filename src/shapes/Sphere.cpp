#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sphere.h"

Sphere::Sphere(float radius, float numSectors, float numStacks)
{
    this->radius = radius;
    this->numSectors = numSectors;
    this->numStacks = numStacks;
}

void Sphere::buildVertices ()
{
    //clear vertices vector
    std::vector<Vector4f>().swap(vertices);
    std::vector<Vector4f>().swap(normalizedVertices);
    std::vector<float>().swap(vertexVector);

    float x {}, y {}, z {};
    float nX {}, nY {}, nZ {};
    float rcos {};
    float nRadius {1.0f/radius};

    float sectorStep {2*pi/numSectors};
    float stackStep {pi/numStacks};
    float sectorAngle {}, stackAngle {};

    int vertexIndex {0};

    for (int i  = 0; i < numStacks; i++) {

        stackAngle = (pi/2) - (i*stackStep);
        rcos = radius * std::cos(stackAngle);
        z = radius * std::sin(stackAngle);
        nZ = z *nRadius;

        for (int j = 0; j < numSectors; j++) {
            sectorAngle = j * sectorStep;

            x = rcos * std::cos(sectorAngle);
            nX = x *nRadius;

            y = rcos * std::sin(sectorAngle);
            nY = y * nRadius;

            Vector4f vertex(x, y, z, vertexIndex);
            Vector4f nVertex(nX, nY, nZ, vertexIndex);

            vertices.push_back(vertex);
            normalizedVertices.push_back(nVertex);

            vertexVector.push_back(x);
            vertexVector.push_back(y);
            vertexVector.push_back(z);

            vertexVector.push_back(0.1);
            vertexVector.push_back(0.4);
            vertexVector.push_back(0.7);

            vertexIndex += 1;
        }
    }

}

void Sphere::generateTriangles()
{
    std::vector<int>().swap(vertexIndex);
    int k1 {}, k2 {};

    for (int i = 0; i < numStacks; i++) {
        k1 = i * numSectors;
        k2 = k1 + numSectors;

        for (int j = 0; j < numSectors; j++, k1++, k2++) {
            if (i != 0) {
                // vertex one
                vertexIndex.push_back(vertices[k1].a);
                //vertex two
                vertexIndex.push_back(vertices[k2].a);
                //vertex three
                vertexIndex.push_back(vertices[k1+1].a);
                numTriangles += 1;
            }

            if (i != (numStacks-1)) {
                // vertex one
                vertexIndex.push_back(vertices[k1+1].a);
                //vertex two
                vertexIndex.push_back(vertices[k2].a);
                //vertex three
                vertexIndex.push_back(vertices[k2+1].a);
                numTriangles += 1;
            }
        }
    }
}

void Sphere::draw()
{
    buildVertices();
    generateTriangles();
}
