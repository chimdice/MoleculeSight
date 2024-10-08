#include "Cylinder.h"

Cylinder::Cylinder(float radius, float length, float numSectors, int instances)
{
    this->radius=radius;
    this->length=length;
    this->numSectors=numSectors;
    this->numInstances=instances;
}

void Cylinder::buildVertices()
{
    std::vector<Vertex>().swap(allVertex);

    float deltaAngle {360/numSectors};
    float angle {0};

    
    for (int j=0; j < numSectors; j++) {
        float x {radius * std::cos(angle*(pi/180))};
        float y {radius * std::sin(angle*(pi/180))};

        Vector3f v1 {x, y, 0};
        Vertex vertex1 {v1};
        allVertex.push_back(vertex1);

        Vector3f v2 {x, y, 1};
        Vertex vertex2 {v2};
        allVertex.push_back(vertex2);

        angle += deltaAngle;
    }
}

void Cylinder::generateTriangles()
{
    std::vector<int>().swap(shapeIndices);

    int k1 {0};
    int k2 {1};
    int end {numSectors*2};

    for (int i = 0; i < numSectors-1; i++) {
        //triangle 1
        shapeIndices.push_back(k1);
        shapeIndices.push_back(k2+2);
        shapeIndices.push_back(k2);

        //triangle 2
        shapeIndices.push_back(k1);
        shapeIndices.push_back(k1+2);
        shapeIndices.push_back(k2+2);

        k1+=2;
        k2+=2;
    }

    //last section
    //triangle 1
    shapeIndices.push_back(k1);
    shapeIndices.push_back(0);
    shapeIndices.push_back(1);

    //triangle 2
    shapeIndices.push_back(k1);
    shapeIndices.push_back(1);
    shapeIndices.push_back(k2);
}

void Cylinder::draw()
{
    buildVertices();
    generateTriangles();
}