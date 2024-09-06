#include "Mesh.h"

void Mesh::render()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, shapeVertices.size()*sizeof(float), shapeVertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapeIndices.size()*sizeof(int), shapeIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0 + sizeof(float)*3);


    glGenBuffers(1, &modelVbo);
    glBindBuffer(GL_ARRAY_BUFFER, modelVbo);
    glBufferData(GL_ARRAY_BUFFER, models.size()*sizeof(float), models.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glBindBuffer(GL_ARRAY_BUFFER, modelVbo);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float)*16, (void*)0);
    glVertexAttribDivisor(2, 1);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float)*16, (void*)0+sizeof(float)*4);
    glVertexAttribDivisor(3, 1);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float)*16, (void*)0+sizeof(float)*8);
    glVertexAttribDivisor(4, 1);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(float)*16, (void*)0+sizeof(float)*12);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, shapeIndices.size(), GL_UNSIGNED_INT, 0, numInstances);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(5);
}

void Mesh::fillModelVector()
{
    std::vector<float>().swap(models);

    for (Matrix4& model: allModelMatrix) {
        for (int i = 0; i < 16; i++) {
            models.push_back(model.matrix[i]);
        }
    }
}

void Mesh::prepareVbo()
{
    std::vector<float>().swap(shapeVertices);

    for (Vertex& vertex:allVertex) {
        shapeVertices.push_back(vertex.vertices.x);
        shapeVertices.push_back(vertex.vertices.y);
        shapeVertices.push_back(vertex.vertices.z);

        vertex.updateNormalVector();
        Vector3f normNormalized = NormalizeVector(vertex.normal);

        shapeVertices.push_back(0);
        shapeVertices.push_back(1);
        shapeVertices.push_back(0);

    }

}

void Mesh::addModelTransformation(Matrix4 matrix)
{
    allModelMatrix.push_back(matrix);
}