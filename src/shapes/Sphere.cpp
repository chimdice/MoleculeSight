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
    std::vector<Vertex>().swap(vertices);

    float psihAngle {90};
    float thetaAngle {0};
    float psiCountBy {180/(numStacks+1)};
    float thetaCountBy {360/numSectors};
    int count  {0};
    
    //top
    Vector3f topVertices {0, 1, 0};
    Vertex vert {topVertices};
    vertices.push_back(vert);
    count += 1;

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
            vertices.push_back(vert2);

            thetaAngle += thetaCountBy;
            count += 1;
        }
        thetaAngle = 0;
    }

    //bottom
    Vector3f botVertices {0, -1, 0};
    Vertex vert3 {botVertices};
    vertices.push_back(vert3);
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

        //top
        vertexIndex.push_back(0);
        vertexIndex.push_back(k2);
        vertexIndex.push_back(k1);

        Vector3f vab {
                        vertices[k1].vertices.x - vertices[0].vertices.x,
                        vertices[k1].vertices.y - vertices[0].vertices.y,
                        vertices[k1].vertices.z - vertices[0].vertices.z
                    };

        Vector3f vac {
                        vertices[k2].vertices.x - vertices[0].vertices.x,
                        vertices[k2].vertices.y - vertices[0].vertices.y,
                        vertices[k2].vertices.z - vertices[0].vertices.z
                    };

        Vector3f norm1 = NormalizeVector(crossProduct(vab, vac));
        vertices[0].allNormals.push_back(norm1);
        vertices[k1].allNormals.push_back(norm1);
        vertices[k2].allNormals.push_back(norm1);

        //bottom
        vertexIndex.push_back(end);
        vertexIndex.push_back(end - k1);
        vertexIndex.push_back(end - k2);

        Vector3f vab2 {
                        vertices[end - k1].vertices.x - vertices[end].vertices.x,
                        vertices[end - k1].vertices.y - vertices[end].vertices.y,
                        vertices[end - k1].vertices.z - vertices[end].vertices.z
                    };

        Vector3f vac2 {
                        vertices[end - k2].vertices.x - vertices[end].vertices.x,
                        vertices[end - k2].vertices.y - vertices[end].vertices.y,
                        vertices[end - k2].vertices.z - vertices[end].vertices.z
                    };

        Vector3f norm2 = NormalizeVector(crossProduct(vab2, vac2));
        vertices[end].allNormals.push_back(norm2);
        vertices[end - k1].allNormals.push_back(norm2);
        vertices[end - k2].allNormals.push_back(norm2);
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

                //triangle 1
                Vector3f vab {
                        vertices[k4].vertices.x - vertices[k3].vertices.x,
                        vertices[k4].vertices.y - vertices[k3].vertices.y,
                        vertices[k4].vertices.z - vertices[k3].vertices.z
                    };

                Vector3f vac {
                                vertices[k5].vertices.x - vertices[k3].vertices.x,
                                vertices[k5].vertices.y - vertices[k3].vertices.y,
                                vertices[k5].vertices.z - vertices[k3].vertices.z
                            };

                Vector3f norm1 = NormalizeVector(crossProduct(vab, vac));
                vertices[k3].allNormals.push_back(norm1);
                vertices[k4].allNormals.push_back(norm1);
                vertices[k5].allNormals.push_back(norm1);

                //triangle 2
                 Vector3f vab2 {
                        vertices[k5].vertices.x - vertices[k4].vertices.x,
                        vertices[k5].vertices.y - vertices[k4].vertices.y,
                        vertices[k5].vertices.z - vertices[k4].vertices.z
                    };

                Vector3f vac2 {
                        vertices[k5+numSectors].vertices.x - vertices[k4].vertices.x,
                        vertices[k5+numSectors].vertices.y - vertices[k4].vertices.y,
                        vertices[k5+numSectors].vertices.z - vertices[k4].vertices.z
                    };

                Vector3f norm2 = NormalizeVector(crossProduct(vab2, vac2));
                vertices[k5+numSectors].allNormals.push_back(norm2);
                vertices[k4].allNormals.push_back(norm2);
                vertices[k5].allNormals.push_back(norm2);

            } else {
                vertexIndex.push_back(k3);
                vertexIndex.push_back(k3+1);
                vertexIndex.push_back(k4);

                vertexIndex.push_back(k4);
                vertexIndex.push_back(k3+1);
                vertexIndex.push_back(k4+1);
                
                //triangle 1
                Vector3f vab {
                        vertices[k4].vertices.x - vertices[k3].vertices.x,
                        vertices[k4].vertices.y - vertices[k3].vertices.y,
                        vertices[k4].vertices.z - vertices[k3].vertices.z
                    };

                Vector3f vac {
                                vertices[k3+1].vertices.x - vertices[k3].vertices.x,
                                vertices[k3+1].vertices.y - vertices[k3].vertices.y,
                                vertices[k3+1].vertices.z - vertices[k3].vertices.z
                            };

                Vector3f norm1 = NormalizeVector(crossProduct(vab, vac));
                vertices[k3].allNormals.push_back(norm1);
                vertices[k4].allNormals.push_back(norm1);
                vertices[k3+1].allNormals.push_back(norm1);

                //triangle 2
                 Vector3f vab2 {
                        vertices[k3+1].vertices.x - vertices[k4].vertices.x,
                        vertices[k3+1].vertices.y - vertices[k4].vertices.y,
                        vertices[k3+1].vertices.z - vertices[k4].vertices.z
                    };

                Vector3f vac2 {
                        vertices[k4+1].vertices.x - vertices[k4].vertices.x,
                        vertices[k4+1].vertices.y - vertices[k4].vertices.y,
                        vertices[k4+1].vertices.z - vertices[k4].vertices.z
                    };

                Vector3f norm2 = NormalizeVector(crossProduct(vab2, vac2));
                vertices[k3+1].allNormals.push_back(norm2);
                vertices[k4].allNormals.push_back(norm2);
                vertices[k4+1].allNormals.push_back(norm2);

            }

            k3+=1;
            k4+=1;
        }
    }
}

void Sphere::prepareVbo()
{
    std::vector<float>().swap(vertexVector);

    for (Vertex& vertex:vertices) {
        vertexVector.push_back(vertex.vertices.x);
        vertexVector.push_back(vertex.vertices.y);
        vertexVector.push_back(vertex.vertices.z);

        vertex.updateNormalVector();
        //std::cout << vertex.normal.x<<" "<< vertex.normal.y<<" "<< vertex.normal.z<<'\n';
        Vector3f normNormalized = NormalizeVector(vertex.normal);
        //std::cout << normNormalized.x<<" "<< normNormalized.y<<" "<< normNormalized.z<<'\n';
        //std::cout << '\n';

        vertexVector.push_back(normNormalized.x);
        vertexVector.push_back(normNormalized.y);
        vertexVector.push_back(normNormalized.z);

    }

}

void Sphere::draw()
{
    buildVertices();
    generateTriangles();
    prepareVbo();
}
