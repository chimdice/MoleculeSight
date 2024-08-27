#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "utility/Camera.cpp"
#include "utility/utility.h"


float width {800.0f};
float height {600.0f};
// Camera
Vector3f pos {0,0,3};
Camera windowCamera (pos, 60.0f, 0.1f, 100.0f, width, height);

//speed
float speed {0.1f};

//free cam
float sensitivity {0.1};
float lastX {400};
float lastY {300};

float angle {0};

void spin ()
{
    angle += 1;
    if (angle > 360)
    {
        angle = 0;
    }
    glutPostRedisplay();
}

static void RenderCB ()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //H2.renderMolecule();

    std::vector<float> testTriangle {
        -0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,
        -0.5f,0.5f,-0.5f,1.0f,0.0f,0.0f,
        0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,
        0.5f,-0.5f,-0.5f,0.0f,1.0f,0.0f,

        -0.5f,-0.5f,0.5f,1.0f,0.0f,1.0f,
        -0.5f,0.5f,0.5f,1.0f,0.0f,1.0f,
        0.5f,0.5f,0.5f,0.0f,1.0f,1.0f,
        0.5f,-0.5f,0.5f,0.0f,1.0f,1.0f
    };

    std::vector<int> testIndex {
        //front
        0,1,2,
        0,2,3,
        //back
        4,5,6,
        4,6,7,
        //sides
        3,2,6,
        3,6,7,
        0,1,5,
        0,5,4,
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
    modelTransform.rotate(rotateModel, -angle);
    Matrix4 newModel = modelTransform.getMatrix();

    glUseProgram(shaderProgram);

    windowCamera.updatePosition(pos);
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
    glCullFace(GL_BACK);
}

void keyboardInput(unsigned char key, int x, int y);
void specialKeyInput (int key, int x, int y);
void mouseEvent (int button, int state, int x, int y);

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
    glutSpecialFunc(specialKeyInput);
    glutMouseFunc(mouseEvent);
    glutIdleFunc(spin);
    glutMainLoop();
    return 0;
}

void keyboardInput(unsigned char key, int x, int y)
{
    Vector3f orien = windowCamera.getOrientation();
    Vector3f move = windowCamera.shiftSide();
    
    switch (key)
    {
    case 'w':
        pos.y += speed;
        glutPostRedisplay();
        break;

    case 's':
        pos.y -= speed;
        glutPostRedisplay();
        break;
    
    case 'd':
        pos.x += speed * move.x;
        pos.y += speed * move.y;
        pos.z += speed * move.z;
        glutPostRedisplay();
        break;

    case 'a':
        pos.x -= speed * move.x;
        pos.y -= speed * move.y;
        pos.z -= speed * move.z;
        glutPostRedisplay();
        break;
    }
}

void specialKeyInput (int key, int x, int y)
{
    Vector3f orien = windowCamera.getOrientation();
    Vector3f move = windowCamera.shiftSide();

    switch (key)
    {
    case 101:
        pos.y += speed;
        glutPostRedisplay();
        break;
    
    case 103:
        pos.y -= speed;
        glutPostRedisplay();
        break;
    
    }
}

void mouseEvent (int button, int state, int x, int y)
{
    float xDiff {x-lastX};
    float yDiff {y-lastY};

    lastX = x;
    lastY = y;

    xDiff *= sensitivity;
    yDiff *= sensitivity;

    std::cout << "x diff is" << xDiff << " and y diff is " << yDiff << ". \n";

}