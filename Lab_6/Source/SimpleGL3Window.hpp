#pragma once
#include "libs.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
class State;

class SimpleGL3Window : public Fl_Gl_Window {
private:
    State* statePtr = nullptr;
    Shader shaderProgram;
    Camera camera;

    GLuint VBO_cube, VAO_cube, EBO_cube;
    GLuint VBO_octahedra, VAO_octahedra, EBO_octahedra;


    bool wasd[4] { false };
    int screenWidth;
    int screenHeight;
    int gl_version_major;
    GLfloat fadeDistance = 40.0f;
    
public:
    SimpleGL3Window(State*, int x, int y, int w, int h);
    void update();

    void loadBuffers();
    void draw(void);
    virtual int handle(int event);
    void Do_Movement();
};