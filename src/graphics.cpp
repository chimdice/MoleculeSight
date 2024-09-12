#include "imgui/imgui.h"
#include "imgui/imgui_impl_glut.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "utility/utility.h"
#include "Math3d.h"
#include "utility/Camera.h"
#include "molecule-components/Molecule.h"

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
Atom h1 (1, 1, 1, 1, 1, 0, 0, 0);
Atom h2 (1, 1, 1, 1, 1, 1, 1, 0);
std::vector<Atom> hs {h1, h2};
Molecule molH (hs);

void keyboardInput(unsigned char key, int x, int y);
void mouseEvent (int x, int y);
void mouseCB (int button, int state, int x, int y);

bool check1 {false};
float slide {0.0f};

static void RenderCB ()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplGLUT_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO();

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

    molH.render();

    ImGui::SetNextWindowSize(ImVec2(width/3, height));
    ImGui::SetNextWindowPos(ImVec2(2*width/3,0));
    ImGui::Begin("MoleculeSight", NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::Text("hi");
    ImVec2 p = ImGui::GetWindowPos();
    ImGui::Text("window pos %.1f %.1f", p.x, p.y);
    ImGui::Checkbox("check 1", &check1);
    ImGui::SliderFloat("slide value", &slide, 0.0f, 1.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
    glutInitWindowSize(width,height);
    glutInitWindowPosition(200, 100);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    int window = glutCreateWindow("MoleculeSight");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    };
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    myInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();

    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = 1/60;
    io.DisplaySize.x = width;
    io.DisplaySize.y = height;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    ImGui_ImplOpenGL3_Init("#version 330");

    glutDisplayFunc(RenderCB);
    glutKeyboardFunc(keyboardInput);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseEvent);
    glutMainLoop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

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
        ImGui_ImplGLUT_MotionFunc(x, y);
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

    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
    glutPostRedisplay();
}
