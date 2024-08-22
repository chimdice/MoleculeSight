#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "molecule-components/Atom.h"
#include "molecule-components/Molecule.h"
#include "molecule-components/Molecule.cpp"
#include "utility/Camera.cpp"
#include "utility/MatrixTransform.cpp"


GLfloat T {0};

//Hydrogen Atom
Atom h1(1, 1, 1, .37, 1, 0, 0, 0);
Atom h2(1, 1, 1, .37, 1, 0.7, 0, 0);
Atom h3(1, 1, 1, .37, 1, 0.7, 0.7, 0);
Atom h4(1, 1, 1, .37, 1, 0.7, 0.7, 0.7);


//H2 molecule
std::vector<Atom> H2Atoms {h1, h2, h3, h4};
Molecule H2 (H2Atoms);

// Camera
Vector3f pos {0,1,7};
Camera windowCamera (pos);

static void RenderCB ()
{
    GLfloat LightPos[] {0,1,0,1};
    GLfloat LightColor[] {1,0,0,1};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, LightColor);
    //windowCamera.Matrix();
    gluLookAt(0,1,3,0,0,0,0,1,0);

    H2.renderMolecule();

    glutSwapBuffers();
}

static void myInit ()
{
    //perspective
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);

    //lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
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

    Matrix4 id {1};
    Vector3f test {1,0,0};
    MatrixTransform idTransfrom {id};
    idTransfrom.print();
    idTransfrom.rotate(test, 90);
    idTransfrom.print();
    glutDisplayFunc(RenderCB);
    glutMainLoop();
    return 0;
}