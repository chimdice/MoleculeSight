#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "utility/Camera.cpp"
#include "utility/utility.h"
//#include "molecule-components/Molecule.cpp"
#include "shapes/Sphere.cpp"


float width {800.0f};
float height {600.0f};
// Camera
Vector3f pos {0,0,3};
Vector3f piv {0,0,0};
Camera windowCamera (pos, 60.0f, 0.1f, 1000.0f, width, height);

float light[3] {0.0f, 1.0f, 0.0f};

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
// Atom h1 (1, 1, 1, 1, 1, 0, 0, 0);
// std::vector<Atom> hs {h1};
// Molecule molH (hs);
// std::vector<Molecule> allMol {molH};

void keyboardInput(unsigned char key, int x, int y);
void mouseEvent (int x, int y);
void mouseCB (int button, int state, int x, int y);

static void RenderCB ()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::string vertexShaderFilePath {"./shaders/shader.vert"};
    std::string fragmentShaderFilePath {"./shaders/shader.frag"};

    std::string vertexShaderFile {};
    std::string fragmentShaderFile {};


    readFile(vertexShaderFilePath, vertexShaderFile);
    readFile(fragmentShaderFilePath, fragmentShaderFile);

    unsigned int shaderProgram {CreateShaders(vertexShaderFile, fragmentShaderFile)};
    glUseProgram(shaderProgram);

    windowCamera.addShader(shaderProgram);
    windowCamera.view();

    int lightLocation {glGetUniformLocation(shaderProgram, "light")};
    glUniform3fv(lightLocation, 1, &light[0]);

    Matrix4 model1 {1.0f};
    MatrixTransform modelTranfrom1 {model1};
    Vector3f translate1 {2.0f, 0.0f, 0.0f};
    modelTranfrom1.translate(translate1);
    Matrix4 model1Final = modelTranfrom1.getMatrix();

    Matrix4 model2 {1.0f};
    MatrixTransform modelTranfrom2 {model2};
    Vector3f translate2 {-2.0f, 0.0f, 0.0f};
    modelTranfrom2.translate(translate2);
    Matrix4 model2Final = modelTranfrom2.getMatrix();

    Sphere sphere {1, 20, 20, 2};
    sphere.addModelTransformation(model1Final);
    sphere.addModelTransformation(model2Final);
    sphere.fillModelVector();
    sphere.draw();
    sphere.prepareVbo();
    sphere.render();

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
