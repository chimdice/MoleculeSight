#include "Framebuffer.h"

FrameBuffer::FrameBuffer(int initalWidth, int initalHeight)
{
    this->width=initalWidth;
    this->height=initalHeight;
}

void FrameBuffer::init()
{
    //framebuffer
    GLuint fbo {0};
    glGenFramebuffers(1, &fbo);

    //colortexture
    GLuint ctbo {0};
    glGenTextures(1, &ctbo);
    glBindTexture(GL_TEXTURE_2D, ctbo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //renderbuffer
    GLuint rbo {0};
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

void FrameBuffer::bindRenderToFBO()
{
    //mols.renderMolecules();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBuffer::bindFBOToScreen(MoleculeList mols)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void FrameBuffer::renderScreen()
{
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
    glBindTexture(GL_TEXTURE_2D, ctbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

bool FrameBuffer::drawOnScreen()
{
    ImGui::SetNextWindowSize(ImVec2(2*width/3, height));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("Scene", NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoScrollWithMouse|ImGuiWindowFlags_NoCollapse);
    ImGui::Image((void*)ctbo, ImVec2(2*width/3, height), ImVec2(0,1), ImVec2(1,0));
    screenOn = ImGui::IsItemHovered();
    ImGui::End();
    return screenOn;
}