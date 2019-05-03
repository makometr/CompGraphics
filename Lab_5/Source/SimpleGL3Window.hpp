#pragma once
#include "libs.hpp"
#include "Shader.hpp"

class SimpleGL3Window : public Fl_Gl_Window {
    Shader shaderProgram;
    GLuint shaderProgram_2 = 0;
    Fl_PNG_Image *texturePNG = nullptr;

    GLuint vertexArrayObject;
    GLuint vertexBuffer;
    GLint positionUniform;
    GLint colourAttribute;
    GLint positionAttribute;
    int gl_version_major;

public:
    SimpleGL3Window(int x, int y, int w, int h);

    void draw(void);
    virtual int handle(int event);
    void reset(void);
};