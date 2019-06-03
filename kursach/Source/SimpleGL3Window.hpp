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
    Shader shaderProgramSkyBox;
    Shader shaderNormals;
    Shader shaderContour;

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
    void draw(void);
    virtual int handle(int event);

private:
    void Do_Movement();
    void loadBuffers();
    unsigned int loadCubemap(const std::vector<std::string> &faces);
    void drawFigure(SceneShape &shape, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection, const glm::vec3 &cameraPos);
    void drawContour(SceneShape &shape, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);
    void drawNormals(SceneShape &shape, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection);
};