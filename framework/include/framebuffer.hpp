#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "glewInc.hpp"

class Framebuffer {
public:
    static Framebuffer &get() {
        static Framebuffer instance;
        return instance;
    }

    void bind();
    void unbind();
    void drawQuad();

    unsigned int getcolorBuffers(int i) { return colorBuffers[i]; }
    unsigned int getpingpongFBO(int i) { return pingpongFBO[i]; }
    unsigned int getpingpongColorBuffers(int i) { return pingpongColorbuffers[i]; }
    unsigned int getTextureID() { return texture; }

private:
    Framebuffer();
    unsigned int attachments[2];
    unsigned int colorBuffers[2];
    unsigned int pingpongFBO[2];
    unsigned int pingpongColorbuffers[2];
    unsigned int texture = 0;
    GLuint hdrFBO = 0;
    GLuint rboDepth = 0;
};

#endif