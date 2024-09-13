#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "../Math3d.h"
#include "../utility/utility.h"

class Mesh
{
    protected:
        std::vector<float> shapeVertices {};
        std::vector<int> shapeIndices {};
        std::vector<Vertex> allVertex {};

        std::vector<Matrix4> allModelMatrix {};
        std::vector<Matrix4> allOutlineMatrix {};
        std::vector<float> models {};
        std::vector<float> outlines {};
        std::vector<float> colorsModel {};
        std::vector<float> colorsOutline {};
        int numInstances {};
        GLuint vao {0};
        GLuint vbo {0}; 
        GLuint ibo {0};
        GLuint modelVbo {0};
        GLuint colorVbo {0};
        void drawObject();
        void drawOutline();

    public:
        void render();
        void fillModelVector();
        void prepareVbo();
        void addModelTransformation(Matrix4 model, Matrix4 outline);
        void addColor(float r, float g, float b)
        {
            colorsModel.push_back(r);
            colorsModel.push_back(g);
            colorsModel.push_back(b);

            colorsOutline.push_back(1);
            colorsOutline.push_back(0);
            colorsOutline.push_back(1);
        }
        
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