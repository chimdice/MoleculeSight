#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "molecule-components/Atom.h"
#include "molecule-components/Molecule.h"
#include "molecule-components/Molecule.cpp"


GLfloat T {0};

//Hydrogen Atom
Atom h1(1, 1, 1, .37, 1, 0, 0, 0);
Atom h2(1, 1, 1, .37, 1, 0.7, 0, 0);
Atom h3(1, 1, 1, .37, 1, 0.7, 0.7, 0);
Atom h4(1, 1, 1, .37, 1, 0.7, 0.7, 0.7);


//H2 molecule
std::vector<Atom> H2Atoms {h1, h2, h3, h4};
Molecule H2 (H2Atoms);

static void Spin ()
{
    T += 0.25;
    if (T > 360) {
        T = 0;
    }
    glutPostRedisplay();
}

static void RenderCB ()
{
    GLfloat LightPos[] {0,1,0,1};
    GLfloat LightColor[] {1,0,0,1};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightColor);
    gluLookAt(0,1,3,0,0,0,0,1,0);

    glRotatef(T, 0, 1, 0);

    


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

    H2.printMass();
    H2.bondLength(0,2);
    H2.bondLength(0,1);
    H2.bondLength(1,2);
    H2.bondAngle(0, 1, 2);
    H2.torsionAngle(0, 1, 2, 3);

    glutDisplayFunc(RenderCB);
    glutIdleFunc(Spin);
    glutMainLoop();
    return 0;
}