#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "utility/Camera.cpp"
#include "utility/utility.h"
#include "molecule-components/Molecule.cpp"


float width {800.0f};
float height {600.0f};
// Camera
Vector3f pos {0,0,3};
Vector3f piv {0,0,0};
Camera windowCamera (pos, 60.0f, 0.1f, 1000.0f, width, height);

//speed
float speed {0.1f};

//free cam
float sensitivity {0.1f};
float lastX {400};
float lastY {300};
int clickDown {};

float angle {0};
float yaw {90.0f};
float pitch {0.0f};

//Molecule
Atom h1 (1, 1, 1, 1, 1, 0, 0, 0);
std::vector<Atom> hs {h1};
Molecule molH (hs);
std::vector<Molecule> allMol {molH};

void keyboardInput(unsigned char key, int x, int y);
void mouseEvent (int x, int y);
void mouseCB (int button, int state, int x, int y);

static void RenderCB ()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float byteTrack {0};
    float byteTrack2 {0};
    std::vector<std::vector<float>> molVertexData {};
    std::vector<std::vector<int>> molVertexIndex {};


    for (Molecule& mol: allMol) {
        mol.createMolecule();
        molVertexData = mol.fillAtomsVertexData();
        molVertexIndex = mol.fillAtomsIndexData();
     }

    float vertexSize = btyeSize2DVector(molVertexData);
    float indexSize = btyeSize2DVector(molVertexIndex);

    std::vector<float> b1 {fillVector(molVertexData)};
    std::vector<int> b2 {fillVector(molVertexIndex)};


    std::string vertexShaderFilePath {"./shaders/shader.vert"};
    std::string fragmentShaderFilePath {"./shaders/shader.frag"};

    std::string vertexShaderFile {};
    std::string fragmentShaderFile {};

    readFile(vertexShaderFilePath, vertexShaderFile);
    readFile(fragmentShaderFilePath, fragmentShaderFile);

    unsigned int shaderProgram {CreateShaders(vertexShaderFile, fragmentShaderFile)};

    //model matrices
    Matrix4 model1 {1.0f};
    Vector3f translate1{-2, 0, 0};
    MatrixTransform modelTransform {model1};
    modelTransform.translate(translate1);
    Matrix4 newModel1 = modelTransform.getMatrix();

    Matrix4 model2 {1.0f};
    Vector3f translate2{2, 0, 0};
    MatrixTransform modelTransform2 {model2};
    modelTransform2.translate(translate2);
    Matrix4 newModel2 = modelTransform2.getMatrix();

    glUseProgram(shaderProgram);

    windowCamera.addShader(shaderProgram);
    windowCamera.view();

    GLuint vertexVbo {0};
    GLuint ibo {0};
    GLuint vao {0};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, b1.size()*sizeof(float), b1.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, b2.size()*sizeof(int), b2.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*3));

    int modelLocation {glGetUniformLocation(shaderProgram, "model")};

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &newModel1.matrix[0]);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, b2.size(), GL_UNSIGNED_INT, NULL);

    // glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &newModel2.matrix[0]);
    // glBindVertexArray(vao);
    // glDrawElements(GL_TRIANGLES, b2.size(), GL_UNSIGNED_INT, NULL);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutSwapBuffers();
}

static void myInit ()
{
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
}


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
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseEvent);
    glutMainLoop();
    return 0;
}

void keyboardInput(unsigned char key, int x, int y)
{
    windowCamera.updatePosition(key);
    glutPostRedisplay();
}

void mouseEvent (int x, int y)
{
    if (clickDown == GLUT_DOWN) {
        float xDiff {x-lastX};
        float yDiff {y-lastY};

        lastX = x;
        lastY = y;

        xDiff *= sensitivity;
        yDiff *= sensitivity;


        windowCamera.rotate(-xDiff, -yDiff);
        glutPostRedisplay();
    }
}

void mouseCB (int button, int state, int x, int y)
{
    lastX = x;
    lastY = y;
    clickDown = state;

    if (button == 3 || button == 4) {
        windowCamera.updateOfov(button);
    }

    glutPostRedisplay();
}
