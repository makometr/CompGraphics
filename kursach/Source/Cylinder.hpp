#include "libs.hpp"

class Cylinder {
private:
    glm::vec3 centerDown {0.0f, -1.0f, 0.0f};
    glm::vec3 centerUp {0.0f, 1.0f, 0.0f};
    GLfloat radiusDown = 1.0f;
    GLfloat radiusUp = 1.0f;
    GLuint VBO_cone[5], VAO_cone[5], EBO_cone[5];
    const int trianglesNum = 60;

public:
    Cylinder() = default;
    void setParams(glm::vec3 o_1, GLfloat c_1, glm::vec3 o_2, GLfloat c_2);
    void loadBuffer();
    void draw(GLuint figureTexture);
    void drawContour();
};

class SceneShape {
private:
    glm::vec3 downCenter;
    GLfloat scaleFactor;
    Cylinder c_1;
    Cylinder c_2;
    Cylinder c_3;
public:
    SceneShape(glm::vec3 center, GLfloat scale);
    void loadBuffer();
    void draw(GLuint figureTexture);
    void drawContour();
};