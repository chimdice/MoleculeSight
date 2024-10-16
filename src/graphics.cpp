#include "imgui/imgui.h"
#include "imgui/imgui_impl_glut.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "./json.hpp"
#include "utility/utility.h"
#include "utility/Framebuffer.h"
#include "Math3d.h"
#include "utility/Camera.h"
#include "molecule-components/MoleculeList.h"

//json
using json = nlohmann::json;
std::ifstream elementFile("element.json");
json elementData = json::parse(elementFile);

//screen
float width {800.0f};
float height {600.0f};

// Camera
Vector3f pos {0,0,3};
Vector3f piv {0,0,0};
Camera windowCamera (pos, 60.0f, 0.1f, 1000.0f, 2*width/3, height);
float light[3] {0.0f, 1.0f, 0.0f};
float speed {0.1f};
float sensitivity {0.1f};
float lastX {400};
float lastY {300};
int clickDown {};
float angle {0};
float yaw {90.0f};
float pitch {0.0f};

//MoleculeList
MoleculeList mols {};

//Menu variables
float selectedRadius {};
float AtomProtonCount {};
float AtomMass {};
std::string currentAtom {};
std::string currentSymbol {};
bool screenOn {false};
int optionRender {0};

//Framebuffer
GLuint fbo {0};
GLuint ctbo {0};
GLuint rbo {0};
std::vector<float> screen {
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
    };

//functions
void keyboardInput(unsigned char key, int x, int y);
void mouseEvent (int x, int y);
void mouseCB (int button, int state, int x, int y);
void createMolecule();
void selectAtom();
void createAtom();
void displayMoleculeInfo();

static void RenderCB ()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

    mols.renderMolecules();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    std::string vertexShaderFilePath2 {"./shaders/frameBufferShader.vert"};
    std::string fragmentShaderFilePath2 {"./shaders/frameBufferShader.frag"};

    std::string vertexShaderFile2 {};
    std::string fragmentShaderFile2 {};


    readFile(vertexShaderFilePath2, vertexShaderFile2);
    readFile(fragmentShaderFilePath2, fragmentShaderFile2);

    unsigned int shaderProgram2 {CreateShaders(vertexShaderFile2, fragmentShaderFile2)};
    glUseProgram(shaderProgram2);

    GLuint screenVao {0};
    glGenVertexArrays(1, &screenVao);
    glBindVertexArray(screenVao);

    GLuint screenVbo {0};
    glGenBuffers(1, &screenVbo);
    glBindBuffer(GL_ARRAY_BUFFER, screenVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, screen.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*)0+sizeof(float)*2);
    
    glBindVertexArray(screenVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glEnable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    ImGui::SetNextWindowSize(ImVec2(width/3, height));
    ImGui::SetNextWindowPos(ImVec2(2*width/3,0));
    ImGui::Begin("MoleculeSight", NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);


    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Create")) {
            if (ImGui::MenuItem("Molcule")) {
                optionRender = 0;
                createMolecule();
            }

            if (ImGui::MenuItem("Atom")) {
                optionRender = 1;
                glutPostRedisplay();
            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    switch (optionRender) {
        case 0: displayMoleculeInfo();
        break;

        case 1: selectAtom();
        break;

        case 2: createAtom();
        break;

    }    

    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(2*width/3, height));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("Scene", NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse|ImGuiWindowFlags_NoCollapse);
    ImGui::Image((void*)ctbo, ImVec2(2*width/3, height), ImVec2(0,1), ImVec2(1,0));
    screenOn = ImGui::IsItemHovered();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}

static void myInit ()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    //glCullFace(GL_BACK);
    //framebuffer
    glGenFramebuffers(1, &fbo);

    //colortexture
    glGenTextures(1, &ctbo);
    glBindTexture(GL_TEXTURE_2D, ctbo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //renderbuffer
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    //bind everything to the frame buffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ctbo, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "frame buffer error ! \n";
    }
}


int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(200, 100);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
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

    //fb.init();

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
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
    glutPostRedisplay();
}

void mouseEvent (int x, int y)
{

    if (clickDown == GLUT_DOWN && screenOn) {
        float xDiff {x-lastX};
        float yDiff {y-lastY};

        lastX = x;
        lastY = y;

        xDiff *= sensitivity;
        yDiff *= sensitivity;


        windowCamera.rotate(-xDiff, -yDiff);
    }

    ImGui_ImplGLUT_MotionFunc(x, y);
    glutPostRedisplay();
}

void mouseCB (int button, int state, int x, int y)
{
    lastX = x;
    lastY = y;
    clickDown = state;

    if ((button == 3 || button == 4)&&screenOn) {
        windowCamera.updateOfov(button);
    }

    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
    glutPostRedisplay();
}

void createMolecule()
{
    Molecule mol {"mol1"};
    mols.addMolecule(mol);
    glutPostRedisplay();
}

void selectAtom()
{
    for (auto& [key, value] : elementData.items()) {
        if (value.contains("radius")) {
            if (ImGui::Button(key.c_str())) {
                currentAtom = key;
                currentSymbol = value.at("symbol");

                std::string mass {value.at("mass")};
                AtomMass = std::stof(mass);

                std::string eleccount {value.at("protons")};
                AtomProtonCount = std::stof(eleccount);

                std::string rad {value.at("radius")};
                selectedRadius = std::stof(rad);

                optionRender = 2;
                glutPostRedisplay();
            }
        }
    }
}

void createAtom()
{
    ImGui::Text(currentAtom.c_str());
    static float xPosition {0.0f};
    static float yPosition {0.0f};
    static float zPosition {0.0f};
    ImGui::InputFloat("X position", &xPosition);
    ImGui::InputFloat("Y position", &yPosition);
    ImGui::InputFloat("Z position", &zPosition);

    if (ImGui::Button("Submit")) {
        Atom a (AtomProtonCount, AtomProtonCount, 4, selectedRadius/170, AtomMass, xPosition, yPosition, zPosition);
        mols.addAtomtoMolecule(0, a);
        optionRender = 0;
        glutPostRedisplay();
    }
}

void displayMoleculeInfo()
{
    mols.showMoleculeNames();
}