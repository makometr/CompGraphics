#pragma once
#include "libs.hpp"
#include "Shader.hpp"

class SimpleGL3Window : public Fl_Gl_Window {
private:
    Shader shaderProgram;
    unsigned char* image = nullptr;
    GLuint texture;
    int width;
    int height;
    GLuint  VAO;

    int gl_version_major;
    GLfloat fadeDistance = 40.0f;

public:
    SimpleGL3Window(int x, int y, int w, int h);

    void loadTexture(const char *file);
    void loadBuffers();
    void draw(void);
    virtual int handle(int event);
    void reset(void);
};