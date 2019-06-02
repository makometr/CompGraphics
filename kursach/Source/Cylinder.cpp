#include "Cylinder.hpp"


void Cylinder::setParams(glm::vec3 o_1, GLfloat c_1, glm::vec3 o_2, GLfloat c_2){
    centerDown = o_1;
    centerUp = o_2;
    radiusDown = c_1;
    radiusUp = c_2;
}

void Cylinder::loadBuffer(){
    int pointsCircleNum = trianglesNum + 1; // +1 for center point

    float vertices_cone[pointsCircleNum * (3+2) * 2]; // 3 for xyz + 2 for texture coords, 2 for two circles
    // float vertices_cone[pointsCircleNum * (3+2+3) * 2]; // 3 for xyz + 2 for texture coords + 3 for normals, 2 for two circles
    // down center
    constexpr GLint elementsPerVert = 5;
    vertices_cone[0] = centerDown.x;
    vertices_cone[1] = centerDown.y;
    vertices_cone[2] = centerDown.z;
    vertices_cone[3] = 0.5f;
    vertices_cone[4] = 0.0f;
    // vertices_cone[5] = 0.0f; // normal
    // vertices_cone[6] = -1.0f; // normal
    // vertices_cone[7] = 0.0f; // normal
    // up center
    vertices_cone[pointsCircleNum * elementsPerVert + 0] = centerUp.x;
    vertices_cone[pointsCircleNum * elementsPerVert + 1] = centerUp.y;
    vertices_cone[pointsCircleNum * elementsPerVert + 2] = centerUp.z;
    vertices_cone[pointsCircleNum * elementsPerVert + 3] = 0.5f;
    vertices_cone[pointsCircleNum * elementsPerVert + 4] = 1.0f;
    // vertices_cone[pointsCircleNum * elementsPerVert + 5] = 0.0f; // normal
    // vertices_cone[pointsCircleNum * elementsPerVert + 6] = 1.0f; // normal
    // vertices_cone[pointsCircleNum * elementsPerVert + 7] = 0.0f; // normal
    // +3 - texture coordinate x
    // +4 - texture coordinate y
    
    float angle = 0.0f;
    float angleStepSize = 360 / trianglesNum;
    float stepTextureCoord = 1.0f / trianglesNum;
    

    for (int i = 1; i < pointsCircleNum; i++, angle += angleStepSize){
        // points for down circle
        auto newXBottom = radiusDown * glm::cos(glm::radians(angle)),
             newZBottom = radiusDown * glm::sin(glm::radians(angle)),
             newXTop = radiusUp * glm::cos(glm::radians(angle)),
             newZTop = radiusUp * glm::sin(glm::radians(angle)),
             heightDelta = centerUp.y-centerDown.y;
        vertices_cone[i*elementsPerVert+0] = newXBottom; // x; 
        vertices_cone[i*elementsPerVert+1] = centerDown.y;  // y
        vertices_cone[i*elementsPerVert+2] = newZBottom; // z
        vertices_cone[i*elementsPerVert+3] = stepTextureCoord * i; // x texture coord;
        vertices_cone[i*elementsPerVert+4] = 0.0f; // y texture coord
        // vertices_cone[i*elementsPerVert+5] = newXTop; // normal
        // vertices_cone[i*elementsPerVert+6] = (newX*newX+newZ*newZ)/heightDelta; // normal
        // vertices_cone[i*elementsPerVert+7] = newZTop; // normal

        // points for up circle
        
        vertices_cone[i*elementsPerVert+0 + pointsCircleNum*elementsPerVert] = newXTop; // x; 
        vertices_cone[i*elementsPerVert+1 + pointsCircleNum*elementsPerVert] = centerUp.y;  // y
        vertices_cone[i*elementsPerVert+2 + pointsCircleNum*elementsPerVert] = newZTop; // z
        vertices_cone[i*elementsPerVert+3 + pointsCircleNum*elementsPerVert] = stepTextureCoord * i; // x texture coord;
        vertices_cone[i*elementsPerVert+4 + pointsCircleNum*elementsPerVert] = 1.0f; // y texture coord
        // vertices_cone[i*elementsPerVert+5 + pointsCircleNum*elementsPerVert] = newXTop; // normal
        // vertices_cone[i*elementsPerVert+6 + pointsCircleNum*elementsPerVert] = (newX*newX+newZ*newZ)/heightDelta; // normal
        // vertices_cone[i*elementsPerVert+7 + pointsCircleNum*elementsPerVert] = newZTop; // normal
    }
    for (int i = 0; i < pointsCircleNum * 2; i++){
        // std::cout << i << ": "
        //           << vertices_cone[i*5+0] << " "
        //           << vertices_cone[i*5+1] << " "
        //           << vertices_cone[i*5+2] << " "
        //           << vertices_cone[i*5+3] << " "
        //           << vertices_cone[i*5+4] << std::endl;
    }
    GLuint indices_cone[(trianglesNum + 2)];
    for (int i = 0; i < trianglesNum + 2; i++){
        indices_cone[i] = i;
        // indices_cone[i + trianglesNum + 2] = i + pointsCircleNum*3;
    }
    indices_cone[trianglesNum + 2 - 1] = indices_cone[1];


    GLuint indices_facet[trianglesNum*2 + 2]; // грань
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
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, elementsPerVert * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, elementsPerVert * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, elementsPerVert * sizeof(GLfloat), (GLvoid*)(5 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO_cone[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cone[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cone), vertices_cone + pointsCircleNum*5, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cone[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_cone), indices_cone, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, elementsPerVert * sizeof(GLfloat), (GLvoid*)(5 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO_cone[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cone[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cone), vertices_cone, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cone[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_facet), indices_facet, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, elementsPerVert * sizeof(GLfloat), (GLvoid*)(5 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cylinder::draw(GLuint figureTexture){
    glBindVertexArray(VAO_cone[0]);
       glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, figureTexture);
    glDrawElements(GL_TRIANGLE_FAN, trianglesNum + 2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO_cone[1]);
           glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, figureTexture);
    glDrawElements(GL_TRIANGLE_FAN, trianglesNum + 2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO_cone[2]);
           glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, figureTexture);
    glDrawElements(GL_TRIANGLE_STRIP, trianglesNum*2+2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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

void SceneShape::draw(GLuint figureTexture){
    c_1.draw(figureTexture);
    c_2.draw(figureTexture);
    c_3.draw(figureTexture);
}