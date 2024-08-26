#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "molecule-components/Atom.h"
#include "molecule-components/Molecule.h"
#include "molecule-components/Molecule.cpp"
#include "utility/Camera.cpp"
#include "utility/utility.h"


GLfloat T {0};

//Hydrogen Atom
Atom h1(1, 1, 1, .37, 1, 0, 0, 0);

//H2 molecule
std::vector<Atom> H2Atoms {h1};
Molecule H2 (H2Atoms);

// Camera
Vector3f pos {0,0,3};
Camera windowCamera (pos, 90.0f, 800.0f/600.0f, 0.0f, 100.0f);


static void RenderCB ()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //H2.renderMolecule();

    std::vector<float> testTriangle {
        -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
        -0.5f,0.5f,0.0f,1.0f,0.0f,0.0f,
        0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,
        0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f
    };

    std::vector<int> testIndex {
        0,1,2,
        0,2,3
    };

    std::string vertexShaderFilePath {"./shaders/shader.vert"};
    std::string fragmentShaderFilePath {"./shaders/shader.frag"};

    std::string vertexShaderFile {};
    std::string fragmentShaderFile {};

    readFile(vertexShaderFilePath, vertexShaderFile);
    readFile(fragmentShaderFilePath, fragmentShaderFile);

    unsigned int shaderProgram {CreateShaders(vertexShaderFile, fragmentShaderFile)};

    //model matrix
    Matrix4 model {1.0f};
    Vector3f rotateModel{0.0f, 1.0f, 0.0f};
    MatrixTransform modelTransform {model};
    //modelTransform.rotate(rotateModel, -60.0f);
    Matrix4 newModel = modelTransform.getMatrix();

    glUseProgram(shaderProgram);

    windowCamera.addShader(shaderProgram);
    windowCamera.view();

    int modelLocation {glGetUniformLocation(shaderProgram, "model")};
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &newModel.matrix[0]);

    GLuint vertexVbo {0};
    GLuint ibo {0};

    GLuint vao {0};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, testTriangle.size()*sizeof(float), testTriangle.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, testIndex.size()*sizeof(int), testIndex.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*3));


    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, testIndex.size(), GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutSwapBuffers();
}

static void myInit ()
{
    glEnable(GL_DEPTH_TEST);
}

void keyboardInput(unsigned char key, int x, int y);

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(200, 100);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutCreateWindow("MoleculeSight");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    };
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    myInit();

    glutDisplayFunc(RenderCB);
    glutKeyboardFunc(keyboardInput);
    glutMainLoop();
    return 0;
}

void keyboardInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        windowCamera.wPress();
        break;
    
    }
}