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
    std::string vertexLightFilePath {"./shaders/light.vert"};
    std::string fragmentLightFilePath {"./shaders/light.frag"};

    std::string vertexShaderFile {};
    std::string fragmentShaderFile {};
    std::string vertexLightFile {};
    std::string fragmentLightFile {};

    readFile(vertexShaderFilePath, vertexShaderFile);
    readFile(fragmentShaderFilePath, fragmentShaderFile);
    readFile(vertexLightFilePath, vertexLightFile);
    readFile(fragmentLightFilePath, fragmentLightFile);

    unsigned int shaderProgram {CreateShaders(vertexShaderFile, fragmentShaderFile)};
    unsigned int lightProgram {CreateShaders(vertexLightFile, fragmentLightFile)};

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

    windowCamera.addShader(shaderProgram, lightProgram);
    windowCamera.view();

    //lighting
    std::vector<float> lightVertices = {
    // front
    -1.0, -1.0,  1.0,
     1.0, -1.0,  1.0,
     1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0,
    // back
    -1.0, -1.0, -1.0,
     1.0, -1.0, -1.0,
     1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0
  };

  std::vector<int> lightIndex = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

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
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    int modelLocation {glGetUniformLocation(shaderProgram, "model")};

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &newModel1.matrix[0]);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, b2.size(), GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(0);

    glUseProgram(lightProgram);
    GLuint vboLight {1};
    GLuint iboLight {1};
    GLuint vaoLight {1};

    glGenVertexArrays(1, &vaoLight);
    glBindVertexArray(vaoLight);

    glGenBuffers(1, &vboLight);
    glBindBuffer(GL_ARRAY_BUFFER, vboLight);
    glBufferData(GL_ARRAY_BUFFER, lightVertices.size()*sizeof(float), lightVertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &iboLight);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboLight);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, lightIndex.size()*sizeof(int), lightIndex.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboLight);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboLight);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    int modelLocation2 {glGetUniformLocation(lightProgram, "model")};

    glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, &newModel2.matrix[0]);
    glBindVertexArray(vaoLight);
    glDrawElements(GL_TRIANGLES, lightIndex.size(), GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(0);

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
