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
    std::vector<Vector3f>().swap(vertices);
    std::vector<Vector3f>().swap(color);
    std::vector<float>().swap(vertexVector);

    float psihAngle {90};
    float thetaAngle {0};
    float psiCountBy {180/(numStacks+1)};
    float thetaCountBy {360/numSectors};
    int count  {0};
    
    //top
    Vector3f topVertices {0, 1, 0};
    Vector3f topColor {1, 0, 0};
    vertices.push_back(topVertices);
    color.push_back(topColor);
    vertexVector.push_back(0);
    vertexVector.push_back(1);
    vertexVector.push_back(0);
    // vertexVector.push_back(topColor.x);
    // vertexVector.push_back(topColor.y);
    // vertexVector.push_back(topColor.z);
    count += 1;

    //middle section
    for (int i = 0; i < numStacks; i++) {
        psihAngle -= psiCountBy;
        float psiRad {psihAngle * (pi/180)};
        float y {radius*std::sin(psiRad)};
        float xz {radius*std::cos(psiRad)};
        Vector3f sectionColor {((float)std::rand()/RAND_MAX), ((float)std::rand()/RAND_MAX), ((float)std::rand()/RAND_MAX)};
        for (int j = 0; j < numSectors; j++) {
            float thetaRad {thetaAngle * (pi/180)};
            float x {xz*std::sin(thetaRad)};
            float z {xz*std::cos(thetaRad)};

            Vector3f vertexData {x, y, z};
            vertices.push_back(vertexData);

            vertexVector.push_back(x);
            vertexVector.push_back(y);
            vertexVector.push_back(z);
            // vertexVector.push_back(sectionColor.x);
            // vertexVector.push_back(sectionColor.y);
            // vertexVector.push_back(sectionColor.z);

            color.push_back(sectionColor);
            thetaAngle += thetaCountBy;
            count += 1;
        }
        thetaAngle = 0;
    }

    //bottom
    Vector3f botVertices {0, -1, 0};
    Vector3f botColor {0, 0, 1};
    vertices.push_back(botVertices);
    color.push_back(botColor);
    vertexVector.push_back(0);
    vertexVector.push_back(-1);
    vertexVector.push_back(0);
    // vertexVector.push_back(botColor.x);
    // vertexVector.push_back(botColor.y);
    // vertexVector.push_back(botColor.z);
    count += 1;
}

void Sphere::generateTriangles()
{
    std::vector<int>().swap(vertexIndex);

    float end {vertices.size()-1};
    //top and bottom triangles
    for (int i = 0; i < numSectors; i++) {
        float k1 {i+1};
        float k2 {};
        if (i == (numSectors-1)) {
            k2 = 1;
        } else {
            k2 = i + 2;
        }

        vertexIndex.push_back(0);
        vertexIndex.push_back(k2);
        vertexIndex.push_back(k1);

        vertexIndex.push_back(end);
        vertexIndex.push_back(end - k1);
        vertexIndex.push_back(end - k2);
    }
    //middle triangles
    for (int i = 0; i < (numStacks-1); i++) {
        float k3 {1 +(i*numSectors)};
        float k4 {k3+numSectors};
        float k5 {};
        for (int j=0; j < numSectors; j++) {

            if (j == (numSectors-1)) {
                k5 = k3 - (numSectors-1);
                vertexIndex.push_back(k3);
                vertexIndex.push_back(k5);
                vertexIndex.push_back(k4);

                vertexIndex.push_back(k4);
                vertexIndex.push_back(k5);
                vertexIndex.push_back(k5+numSectors);
                // std::cout << k3 <<" "<< k5 <<" "<< k4 <<"\n";
                // std::cout << k4 <<" "<< k5 <<" "<< k5+numSectors <<"\n";
            } else {
                vertexIndex.push_back(k3);
                vertexIndex.push_back(k3+1);
                vertexIndex.push_back(k4);

                vertexIndex.push_back(k4);
                vertexIndex.push_back(k3+1);
                vertexIndex.push_back(k4+1);
                // std::cout << k3 <<" "<< k3+1 <<" "<< k4 <<"\n";
                // std::cout << k4 <<" "<< k3+1 <<" "<< k4+1 <<"\n";
            }

            k3+=1;
            k4+=1;
        }
    }
}

void Sphere::draw()
{
    buildVertices();
    generateTriangles();
}
