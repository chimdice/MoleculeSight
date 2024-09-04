#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "../Math3d.h"

class Mesh
{
    protected:
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
        void fillModelVector();
        void prepareVbo();
        void addModelTransformation(Matrix4 matrix);
        void addNumInstances()
        {
            numInstances += 1;
        }

        std::vector<float> getVertices ()
        {
            return shapeVertices;
        }

        std::vector<float> getModels ()
        {
            return models;
        }

        std::vector<int> getIndices ()
        {
            return shapeIndices;
        }
};

#endif