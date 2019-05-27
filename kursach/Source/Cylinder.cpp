#include "Cylinder.hpp"


Cylinder::setParams(glm::vec3 o_1, GLfloat c_1, glm::vec3 o_2, GLfloat c_2){
    centerDown = o_1;
    centerUp = o_2;
    radiusDown = c_1;
    radiusUp = c_2;
}

void Cylinder::loadBuffer(){
    int pointsCircleNum = trianglesNum + 1; // +1 for center point

    float vertices_cone[pointsCircleNum * 3 * 2]; // 3 for xyz, 2 for two circles
    // down center
    vertices_cone[0] = centerDown.x;
    vertices_cone[1] = centerDown.y;
    vertices_cone[2] = centerDown.z;
    // up center
    vertices_cone[pointsCircleNum * 3 + 0] = centerUp.x;
    vertices_cone[pointsCircleNum * 3 + 1] = centerUp.y;
    vertices_cone[pointsCircleNum * 3 + 2] = centerUp.z;
    
    float angle = 0.0f;
    float angleStepSize = 360 / trianglesNum;
    
    for (int i = 1; i < pointsCircleNum; i++, angle += angleStepSize){
        // points for down circle
        vertices_cone[i*3+0] = radiusDown * glm::cos(glm::radians(angle)); // x; 
        vertices_cone[i*3+1] = centerDown.y;  // y
        vertices_cone[i*3+2] = radiusDown * glm::sin(glm::radians(angle)); // z
        // points for up circle
        vertices_cone[i*3+0 + pointsCircleNum*3] = radiusUp * glm::cos(glm::radians(angle)); // x; 
        vertices_cone[i*3+1 + pointsCircleNum*3] = centerUp.y;  // y
        vertices_cone[i*3+2 + pointsCircleNum*3] = radiusUp * glm::sin(glm::radians(angle)); // z
    }
    for (int i = 0; i < pointsCircleNum * 2; i++){
        std::cout << i << ": " << vertices_cone[i*3+0] << " " << vertices_cone[i*3+1] << " " << vertices_cone[i*3+2] << std::endl;
    }
    GLuint indices_cone[(trianglesNum + 2)];
    for (int i = 0; i < trianglesNum + 2; i++){
        indices_cone[i] = i;
        // indices_cone[i + trianglesNum + 2] = i + pointsCircleNum*3;
    }
    indices_cone[trianglesNum + 2 - 1] = indices_cone[1];


    GLuint indices_facet[trianglesNum*2 + 2];
    for (int i = 0; i < trianglesNum; i++){
        indices_facet[i*2] = i + trianglesNum + 2;
        indices_facet[i*2 + 1] = i + 1;
    }
    indices_facet[trianglesNum*2] = indices_facet[0];
    indices_facet[trianglesNum*2+1] = indices_facet[1];

    for (int i = 0; i < trianglesNum*2 + 2; i++)
        std::cout << indices_facet[i] << " ";
    std::cout << std::endl;


    glGenVertexArrays(3, VAO_cone);
    glGenBuffers(3, VBO_cone);
    glGenBuffers(3, EBO_cone);

    glBindVertexArray(VAO_cone[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cone[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cone), vertices_cone, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cone[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_cone), indices_cone, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO_cone[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cone[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cone), vertices_cone + pointsCircleNum*3, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cone[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_cone), indices_cone, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO_cone[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cone[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cone), vertices_cone, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cone[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_facet), indices_facet, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cylinder::draw(){
    glBindVertexArray(VAO_cone[0]);
    glDrawElements(GL_TRIANGLE_FAN, trianglesNum + 2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO_cone[1]);
    glDrawElements(GL_TRIANGLE_FAN, trianglesNum + 2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO_cone[2]);
    glDrawElements(GL_TRIANGLE_STRIP, trianglesNum*2, GL_UNSIGNED_INT, 0);
}


SceneShape::SceneShape(glm::vec3 center, GLfloat scale):
   downCenter(center), scaleFactor(scale)
{
    c_1.setParams(glm::vec3{0.0f, -1.0f, 0.0f}, 1.0f, glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f);
    c_2.setParams(glm::vec3{0.0f, 0.0f, 0.0f}, 0.80f, glm::vec3{0.0f, 0.6f, 0.0f}, 0.80f);
    c_3.setParams(glm::vec3{0.0f, 0.6f, 0.0f}, 1.00f, glm::vec3{0.0f, 1.0f, 0.0f}, 0.0f);
}

void SceneShape::loadBuffer(){
    c_1.loadBuffer();
    c_2.loadBuffer();
    c_3.loadBuffer();
}

void SceneShape::draw(){
    c_1.draw();
    c_2.draw();
    c_3.draw();
}