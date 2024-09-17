#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

class FrameBuffer
{
    private:
        GLuint fbo {0};
        GLuint ctbo {0};
        GLuint rbo {0};

        int width {};
        int height {};

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
        void bindRenderToFBO();
        void bindFBOToScreen();
        void renderScreen();

        GLuint getTexture()
        {
            return ctbo;
        }
};