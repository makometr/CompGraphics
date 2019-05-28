#pragma once
#include "libs.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Cylinder.hpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
class State;

class SimpleGL3Window : public Fl_Gl_Window {
private:
    State* statePtr = nullptr;
    Shader shaderProgramFigures;
    Shader shaderProgramAxes;
    Shader shaderProgramSkyBox;
    GLuint cubemapTexture;
    Camera camera {glm::vec3{0.0f, 0.0f, 3.0f}};

    SceneShape shape_1 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    SceneShape shape_2 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    SceneShape shape_3 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    SceneShape shape_4 {glm::vec3{0.0f, -1.0f, 0.0f}, 0.1f};
    GLuint VBO_axes, VAO_axes;
    GLuint skyboxVAO, skyboxVBO;

    bool wasd[4] { false };
    int screenWidth;
    int screenHeight;
    int gl_version_major;

public:
    SimpleGL3Window(State*, int x, int y, int w, int h);
    void update();

    unsigned int loadCubemap(std::vector<std::string> faces);

    void loadBuffers();
    void draw(void);
    virtual int handle(int event);
    void Do_Movement();
};