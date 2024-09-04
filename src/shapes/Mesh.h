#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "./Math3d.h"

class Mesh
{
    private:
        std::vector<float> shapeVertices {};
        std::vector<int> shapeIndices {};
        std::vector<Vertex> allVertex {};

        std::vector<Matrix4> allModelMatrix {};
        std::vector<float> models {};
        int numInstances {};
        GLuint vao {0};
        GLuint vbo {0}; 
        GLuint ibo {0};
        GLuint modelVbo {0};

    public:
        void render();
};

#endif