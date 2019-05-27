#pragma once
#include "libs.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Cylinder.hpp"
class State;

class SimpleGL3Window : public Fl_Gl_Window {
private:
    State* statePtr = nullptr;
    Shader shaderProgramFigures;
    Shader shaderProgramAxes;
    Camera camera;

    SceneShape shape_1 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    SceneShape shape_2 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    SceneShape shape_3 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    SceneShape shape_4 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    GLuint VBO_axes, VAO_axes;

    bool wasd[4] { false };
    int screenWidth;
    int screenHeight;
    int gl_version_major;
    GLfloat fadeDistance = 40.0f;

public:
    SimpleGL3Window(State*, int x, int y, int w, int h);
    void update();


    void CreateCone(glm::vec3 p1, glm::vec3 p2, double r1, double r2, int m, double theta1, double theta2);

    void loadBuffers();
    void draw(void);
    virtual int handle(int event);
    void Do_Movement();
};