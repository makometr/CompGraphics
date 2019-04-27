#pragma once
#include "libs.hpp"

void add_output(const char *format, ...);

class SimpleGL3Window : public Fl_Gl_Window {
    GLuint shaderProgram;
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