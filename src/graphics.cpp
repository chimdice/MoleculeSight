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

    //std::cout << b1.size() <<" and "<<b2.size()<<'\n';

    // std::vector<float> b1 {
    //     -0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,
    //     -0.5f,0.5f,-0.5f,1.0f,0.0f,0.0f,
    //     0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,
    //     0.5f,-0.5f,-0.5f,0.0f,1.0f,0.0f,

    //     -0.5f,-0.5f,0.5f,1.0f,0.0f,1.0f,
    //     -0.5f,0.5f,0.5f,1.0f,0.0f,1.0f,
    //     0.5f,0.5f,0.5f,0.0f,1.0f,1.0f,
    //     0.5f,-0.5f,0.5f,0.0f,1.0f,1.0f
    // };

    // std::vector<int> b2 {
         //front
    //     0,1,2,
    //     0,2,3,
         //back
    //     4,5,6,
    //     4,6,7,
         //sides
    //     3,2,6,
    //     3,6,7,
    //     0,1,5,
    //     0,5,4,
    // };

    std::string vertexShaderFilePath {"./shaders/shader.vert"};
    std::string fragmentShaderFilePath {"./shaders/shader.frag"};

    std::string vertexShaderFile {};
    std::string fragmentShaderFile {};

    readFile(vertexShaderFilePath, vertexShaderFile);
    readFile(fragmentShaderFilePath, fragmentShaderFile);

    unsigned int shaderProgram {CreateShaders(vertexShaderFile, fragmentShaderFile)};

    //model matrix
    Matrix4 model {1.0f};
    Vector3f rotateModel{0.1f};
    MatrixTransform modelTransform {model};
    //modelTransform.rotate(rotateModel, -angle);
    //modelTransform.scale(rotateModel);
    Matrix4 newModel = modelTransform.getMatrix();

    glUseProgram(shaderProgram);

    //windowCamera.updatePosition(pos);
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
    glBufferData(GL_ARRAY_BUFFER, b1.size()*sizeof(float), b1.data(), GL_STATIC_DRAW);
    // for (int i = 0; i < molVertexData.size(); i++) {
    //     glBufferSubData(GL_ARRAY_BUFFER, byteTrack, byteTrack+ molVertexSize[i], molVertexData[i].data());
    //     byteTrack += molVertexSize[i];
    // }
    //glBufferSubData(GL_ARRAY_BUFFER, byteTrack, byteTrack+ molVertexSize[0], molVertexData[0].data());

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, b2.size()*sizeof(int), b2.data(), GL_STATIC_DRAW);
    // for (int i = 0; i < molVertexIndex.size(); i++) {
    //     glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, byteTrack2, byteTrack2+ molIndexSize[i], molVertexIndex[i].data());
    //     byteTrack2 += molIndexSize[i];
    // }
    //glBufferSubData(GL_ARRAY_BUFFER, byteTrack2, byteTrack2+ molIndexSize[0], molVertexIndex[0].data());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*3));


    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, b2.size(), GL_UNSIGNED_INT, NULL);
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
void mouseEvent (int x, int y);
void mouseCB (int button, int state, int x, int y);


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
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseEvent);
    //glutIdleFunc(spin);
    glutMainLoop();
    return 0;
}

void keyboardInput(unsigned char key, int x, int y)
{
    
    // switch (key)
    // {
    // case 's':
    //     pos.y += speed;
    //     piv.y += speed;
    //     break;

    // case 'w':
    //     pos.y -= speed;
    //     piv.y -= speed;
    //     break;
    
    // case 'a':
    //     pos.x += speed * move.x;
    //     pos.y += speed * move.y;
    //     pos.z += speed * move.z;

    //     piv.x += speed * move.x;
    //     piv.y += speed * move.y;
    //     piv.z += speed * move.z;
    //     break;

    // case 'd':
    //     pos.x -= speed * move.x;
    //     pos.y -= speed * move.y;
    //     pos.z -= speed * move.z;

    //     piv.x -= speed * move.x;
    //     piv.y -= speed * move.y;
    //     piv.z -= speed * move.z;
    //     break;
    // }

    windowCamera.updatePosition(key);
    glutPostRedisplay();
}

void specialKeyInput (int key, int x, int y)
{
    
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

    // if (yaw > 0) {
    //     yaw -= 360;
    // } else if (yaw < -360) {
    //     yaw += 360;
    // }

    // if (pitch > 89) {
    //     pitch = 89;
    // } else if (pitch < -89) {
    //     pitch = -89;
    // }

    // std::cout << " yaw value is " << yaw << ". \n";
    // windowCamera.rotate(yaw, pitch);
    // glutPostRedisplay();
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