#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glut.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../molecule-components/MoleculeList.h"

class FrameBuffer
{
    private:
        GLuint fbo {0};
        GLuint ctbo {0};
        GLuint rbo {0};

        int width {};
        int height {};
        bool screenOn {};

        std::vector<float> screen {
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
    };

    public:
        FrameBuffer(int initalWidth, int initalHeight);
        void init();
        void bindRenderToFBO();
        void bindFBOToScreen(MoleculeList mols);
        void renderScreen();
        bool drawOnScreen();
};