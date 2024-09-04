#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sphere.h"

Sphere::Sphere(float radius, float numSectors, float numStacks, int instances)
{
    this->radius = radius;
    this->numSectors = numSectors;
    this->numStacks = numStacks;
    this->numInstances=instances;
}

void Sphere::buildVertices ()
{
    //clear vertices vector
    std::vector<Vertex>().swap(allVertex);

    float psihAngle {90};
    float thetaAngle {0};
    float psiCountBy {180/(numStacks+1)};
    float thetaCountBy {360/numSectors};
    
    //top
    Vector3f topVertices {0, 1, 0};
    Vertex vert {topVertices};
    allVertex.push_back(vert);

    //middle section
    for (int i = 0; i < numStacks; i++) {
        psihAngle -= psiCountBy;
        float psiRad {psihAngle * (pi/180)};
        float y {radius*std::sin(psiRad)};
        float xz {radius*std::cos(psiRad)};
        for (int j = 0; j < numSectors; j++) {
            float thetaRad {thetaAngle * (pi/180)};
            float x {xz*std::sin(thetaRad)};
            float z {xz*std::cos(thetaRad)};

            Vector3f vertexData {x, y, z};
            Vertex vert2 {vertexData};
            allVertex.push_back(vert2);

            thetaAngle += thetaCountBy;
        }
        thetaAngle = 0;
    }

    //bottom
    Vector3f botVertices {0, -1, 0};
    Vertex vert3 {botVertices};
    allVertex.push_back(vert3);
}

void Sphere::generateTriangles()
{
    std::vector<int>().swap(shapeIndices);

    float end {allVertex.size()-1};
    //top and bottom triangles
    for (int i = 0; i < numSectors; i++) {
        float k1 {i+1};
        float k2 {};
        if (i == (numSectors-1)) {
            k2 = 1;
        } else {
            k2 = i + 2;
        }

        //top
        shapeIndices.push_back(0);
        shapeIndices.push_back(k2);
        shapeIndices.push_back(k1);

        Vector3f vab {
                        allVertex[k1].vertices.x - allVertex[0].vertices.x,
                        allVertex[k1].vertices.y - allVertex[0].vertices.y,
                        allVertex[k1].vertices.z - allVertex[0].vertices.z
                    };

        Vector3f vac {
                        allVertex[k2].vertices.x - allVertex[0].vertices.x,
                        allVertex[k2].vertices.y - allVertex[0].vertices.y,
                        allVertex[k2].vertices.z - allVertex[0].vertices.z
                    };

        Vector3f norm1 = NormalizeVector(crossProduct(vab, vac));
        allVertex[0].allNormals.push_back(norm1);
        allVertex[k1].allNormals.push_back(norm1);
        allVertex[k2].allNormals.push_back(norm1);

        //bottom
        shapeIndices.push_back(end);
        shapeIndices.push_back(end - k1);
        shapeIndices.push_back(end - k2);

        Vector3f vab2 {
                        allVertex[end - k1].vertices.x - allVertex[end].vertices.x,
                        allVertex[end - k1].vertices.y - allVertex[end].vertices.y,
                        allVertex[end - k1].vertices.z - allVertex[end].vertices.z
                    };

        Vector3f vac2 {
                        allVertex[end - k2].vertices.x - allVertex[end].vertices.x,
                        allVertex[end - k2].vertices.y - allVertex[end].vertices.y,
                        allVertex[end - k2].vertices.z - allVertex[end].vertices.z
                    };

        Vector3f norm2 = NormalizeVector(crossProduct(vab2, vac2));
        allVertex[end].allNormals.push_back(norm2);
        allVertex[end - k1].allNormals.push_back(norm2);
        allVertex[end - k2].allNormals.push_back(norm2);
    }
    //middle triangles
    for (int i = 0; i < (numStacks-1); i++) {
        float k3 {1 +(i*numSectors)};
        float k4 {k3+numSectors};
        float k5 {};
        for (int j=0; j < numSectors; j++) {

            if (j == (numSectors-1)) {
                k5 = k3 - (numSectors-1);
                shapeIndices.push_back(k3);
                shapeIndices.push_back(k5);
                shapeIndices.push_back(k4);

                shapeIndices.push_back(k4);
                shapeIndices.push_back(k5);
                shapeIndices.push_back(k5+numSectors);

                //triangle 1
                Vector3f vab {
                        allVertex[k4].vertices.x - allVertex[k3].vertices.x,
                        allVertex[k4].vertices.y - allVertex[k3].vertices.y,
                        allVertex[k4].vertices.z - allVertex[k3].vertices.z
                    };

                Vector3f vac {
                                allVertex[k5].vertices.x - allVertex[k3].vertices.x,
                                allVertex[k5].vertices.y - allVertex[k3].vertices.y,
                                allVertex[k5].vertices.z - allVertex[k3].vertices.z
                            };

                Vector3f norm1 = NormalizeVector(crossProduct(vab, vac));
                allVertex[k3].allNormals.push_back(norm1);
                allVertex[k4].allNormals.push_back(norm1);
                allVertex[k5].allNormals.push_back(norm1);

                //triangle 2
                 Vector3f vab2 {
                        allVertex[k5].vertices.x - allVertex[k4].vertices.x,
                        allVertex[k5].vertices.y - allVertex[k4].vertices.y,
                        allVertex[k5].vertices.z - allVertex[k4].vertices.z
                    };

                Vector3f vac2 {
                        allVertex[k5+numSectors].vertices.x - allVertex[k4].vertices.x,
                        allVertex[k5+numSectors].vertices.y - allVertex[k4].vertices.y,
                        allVertex[k5+numSectors].vertices.z - allVertex[k4].vertices.z
                    };

                Vector3f norm2 = NormalizeVector(crossProduct(vab2, vac2));
                allVertex[k5+numSectors].allNormals.push_back(norm2);
                allVertex[k4].allNormals.push_back(norm2);
                allVertex[k5].allNormals.push_back(norm2);

            } else {
                shapeIndices.push_back(k3);
                shapeIndices.push_back(k3+1);
                shapeIndices.push_back(k4);

                shapeIndices.push_back(k4);
                shapeIndices.push_back(k3+1);
                shapeIndices.push_back(k4+1);
                
                //triangle 1
                Vector3f vab {
                        allVertex[k4].vertices.x - allVertex[k3].vertices.x,
                        allVertex[k4].vertices.y - allVertex[k3].vertices.y,
                        allVertex[k4].vertices.z - allVertex[k3].vertices.z
                    };

                Vector3f vac {
                                allVertex[k3+1].vertices.x - allVertex[k3].vertices.x,
                                allVertex[k3+1].vertices.y - allVertex[k3].vertices.y,
                                allVertex[k3+1].vertices.z - allVertex[k3].vertices.z
                            };

                Vector3f norm1 = NormalizeVector(crossProduct(vab, vac));
                allVertex[k3].allNormals.push_back(norm1);
                allVertex[k4].allNormals.push_back(norm1);
                allVertex[k3+1].allNormals.push_back(norm1);

                //triangle 2
                 Vector3f vab2 {
                        allVertex[k3+1].vertices.x - allVertex[k4].vertices.x,
                        allVertex[k3+1].vertices.y - allVertex[k4].vertices.y,
                        allVertex[k3+1].vertices.z - allVertex[k4].vertices.z
                    };

                Vector3f vac2 {
                        allVertex[k4+1].vertices.x - allVertex[k4].vertices.x,
                        allVertex[k4+1].vertices.y - allVertex[k4].vertices.y,
                        allVertex[k4+1].vertices.z - allVertex[k4].vertices.z
                    };

                Vector3f norm2 = NormalizeVector(crossProduct(vab2, vac2));
                allVertex[k3+1].allNormals.push_back(norm2);
                allVertex[k4].allNormals.push_back(norm2);
                allVertex[k4+1].allNormals.push_back(norm2);

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
