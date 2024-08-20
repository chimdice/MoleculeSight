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
    std::vector<Vector3f>().swap(normalizedVertices);

    float x {}, y {}, z {};
    float nX {}, nY {}, nZ {};
    float rcos {};
    float nRadius {1.0f/radius};

    float sectorStep {2*pi/numSectors};
    float stackStep {pi/numStacks};
    float sectorAngle {}, stackAngle {};

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

            Vector3f vertex(x, y, z);
            Vector3f nVertex(nX, nY, nZ);

            vertices.push_back(vertex);
            normalizedVertices.push_back(nVertex);
        }
    }

}

void Sphere::generateTriangles()
{
    std::vector<float>().swap(sphereTriangles);
    int k1 {}, k2 {};

    for (int i = 0; i < numStacks; i++) {
        k1 = i * numSectors;
        k2 = k1 + numSectors;

        for (int j = 0; j < numSectors; j++, k1++, k2++) {
            if (i != 0) {
                // vertex one
                sphereTriangles.push_back(normalizedVertices[k1].x);
                sphereTriangles.push_back(normalizedVertices[k1].y);
                sphereTriangles.push_back(normalizedVertices[k1].z);
                //vertex two
                sphereTriangles.push_back(normalizedVertices[k2].x);
                sphereTriangles.push_back(normalizedVertices[k2].y);
                sphereTriangles.push_back(normalizedVertices[k2].z);
                //vertex three
                sphereTriangles.push_back(normalizedVertices[k1+1].x);
                sphereTriangles.push_back(normalizedVertices[k1+1].y);
                sphereTriangles.push_back(normalizedVertices[k1+1].z);
                //color
                sphereTrianglesColor.insert(sphereTrianglesColor.end(), {1,0,0, 1,0,0, 1,0,0});
                numTriangles += 1;
            }

            if (i != (numStacks-1)) {
                 // vertex one
                sphereTriangles.push_back(normalizedVertices[k1+1].x);
                sphereTriangles.push_back(normalizedVertices[k1+1].y);
                sphereTriangles.push_back(normalizedVertices[k1+1].z);
                //vertex two
                sphereTriangles.push_back(normalizedVertices[k2].x);
                sphereTriangles.push_back(normalizedVertices[k2].y);
                sphereTriangles.push_back(normalizedVertices[k2].z);
                //vertex three
                sphereTriangles.push_back(normalizedVertices[k2+1].x);
                sphereTriangles.push_back(normalizedVertices[k2+1].y);
                sphereTriangles.push_back(normalizedVertices[k2+1].z);
                //color
                sphereTrianglesColor.insert(sphereTrianglesColor.end(), {0,0,1, 0,0,1, 0,0,1});
                numTriangles += 1;
            }
        }
    }
}

void Sphere::draw()
{
    buildVertices();
    generateTriangles();

    // std::vector<float> testPoint {
    //     0,0,0, 1,1,0, -1,1,0,
    //     0,0,0, -1,-1,0, 1,-1,0
    // };

    // GLuint vertexVbo {0};
    // GLuint colorVbo {0};

    // glGenBuffers(1, &vertexVbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    // glBufferData(GL_ARRAY_BUFFER, numTriangles*sizeof(float)*9, &sphereTriangles.front(), GL_STATIC_DRAW);
    
    // glGenBuffers(1, &colorVbo);
    // glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    // glBufferData(GL_ARRAY_BUFFER, numTriangles*sizeof(float)*9, &sphereTriangles.front(), GL_STATIC_DRAW);

    // GLuint vao {0};
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // glDrawArrays(GL_TRIANGLES, 0, 3*numTriangles);
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);

}
