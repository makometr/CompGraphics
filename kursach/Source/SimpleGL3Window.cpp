#include "SimpleGL3Window.hpp"
#include "State.hpp"

SimpleGL3Window::SimpleGL3Window(State* ptr, int x, int y, int w, int h) :  Fl_Gl_Window(x, y, w, h){
    statePtr = ptr; 
    mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
    screenWidth = this->w();
    screenHeight = this->h();
}

void SimpleGL3Window::draw(void) {
    glEnable(GL_DEPTH_TEST);
    shaderProgramFigures.readAndCompile("Shaders/vertex_figures.shader", "Shaders/fragment_figures.shader");
    shaderProgramAxes.readAndCompile("Shaders/vertex_axes.shader", "Shaders/fragment.shader");
    shaderProgramSkyBox.readAndCompile("Shaders/vertex_map.shader", "Shaders/fragment_map.shader");
    shaderNormals.readAndCompile("Shaders/vertex_normal.shader", "Shaders/fragment_normal.shader", "Shaders/geometry_normal.shader");
    shaderContour.readAndCompile("Shaders/vertex_contour.shader", "Shaders/fragment_contour.shader");
    shaderProgramSkyBox.Use();
    shaderProgramSkyBox.setInt("skybox", 0);
    shaderProgramFigures.Use();
    shaderProgramFigures.setInt("skybox", 0);
    loadBuffers();
    Do_Movement();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.4f, 0.0f));
    model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(camera.Zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 50.0f);
    auto color = statePtr->getRGB();
    shaderProgramFigures.setVec3("aColor", glm::vec3{color[0], color[1], color[2]});
    
    drawFigure(shape_1, model, view, projection, camera.Position);
    drawContour(shape_1, model, view, projection);
    if (statePtr->getIsNormalsDrawn())
        drawNormals(shape_1, model, view, projection);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.1f, 0.7f, 0.0f));
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
    drawFigure(shape_2, model, view, projection, camera.Position);
    drawContour(shape_2, model, view, projection);
    if (statePtr->getIsNormalsDrawn())
        drawNormals(shape_2, model, view, projection);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.1f, 0.7f, 0.0f));
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
    drawFigure(shape_3, model, view, projection, camera.Position);
    drawContour(shape_3, model, view, projection);
    if (statePtr->getIsNormalsDrawn())
        drawNormals(shape_3, model, view, projection);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 2.6f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    drawFigure(shape_4, model, view, projection, camera.Position);
    drawContour(shape_4, model, view, projection);
    if (statePtr->getIsNormalsDrawn())
        drawNormals(shape_4, model, view, projection);

    // axes
    if (statePtr->getIsAxesDrawn()){
        shaderProgramAxes.Use();
        glm::mat4 modelAxe = glm::scale(glm::mat4(1.0f), glm::vec3(100, 100, 100));
        glm::mat4 viewAxe = camera.GetViewMatrix();
        glm::mat4 projectionAxe = glm::perspective(camera.Zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 50.0f);

        shaderProgramAxes.setMat4("model", modelAxe);
        shaderProgramAxes.setMat4("view", viewAxe);
        shaderProgramAxes.setMat4("projection", projectionAxe);

        glBindVertexArray(VAO_axes);
        glLineWidth(2.0f);
        glDrawArrays(GL_LINES, 0, 6*3);
        glBindVertexArray(0);
    }

    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    shaderProgramSkyBox.Use();
    model = glm::mat4(1.0f);
    view = camera.GetViewMatrix();
    projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
    shaderProgramSkyBox.setMat4("view", view);
    shaderProgramSkyBox.setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}

void SimpleGL3Window::drawNormals(SceneShape &shape, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection){
    shaderNormals.Use();
    shaderNormals.setMat4("projection", projection);
    shaderNormals.setMat4("view", view);
    shaderNormals.setMat4("model", model);
    shape.draw(cubemapTexture);
}

void SimpleGL3Window::drawContour(SceneShape &shape, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection){
    shaderContour.Use();
    shaderContour.setMat4("projection", projection);
    shaderContour.setMat4("view", view);
    shaderContour.setMat4("model", model);
    shape.drawContour();
}

void SimpleGL3Window::drawFigure(SceneShape &shape, const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection, const glm::vec3 &cameraPos){
    shaderProgramFigures.Use();
    shaderProgramFigures.setMat4("model", model);
    shaderProgramFigures.setMat4("view", view);
    shaderProgramFigures.setMat4("projection", projection);
    shaderProgramFigures.setVec3("cameraPos", camera.Position);
    shape.draw(cubemapTexture);
}

void SimpleGL3Window::Do_Movement() {
    // Camera controls
    if(wasd[0])
        camera.ProcessKeyboard(FORWARD);
    if(wasd[2])
        camera.ProcessKeyboard(BACKWARD);
    if(wasd[1])
        camera.ProcessKeyboard(LEFT);
    if(wasd[3])
        camera.ProcessKeyboard(RIGHT);
}

void SimpleGL3Window::loadBuffers(){
    static bool isLoaded = false;
    if (isLoaded)
        return;
    shape_1.loadBuffer();
    shape_2.loadBuffer();
    shape_3.loadBuffer();
    shape_4.loadBuffer();

    float vertices_axes[] = {
        -1.0,  0.0,  0.0, 1.0,  0.0,  0.0,
         1.0,  0.0,  0.0, 1.0,  0.0,  0.0,
         0.0, -1.0,  0.0, 0.0,  1.0,  0.0,
         0.0,  1.0,  0.0, 0.0,  1.0,  0.0,
         0.0,  0.0, -1.0, 0.0,  0.0,  1.0,
         0.0,  0.0,  1.0, 0.0,  0.0,  1.0,
    };
    glGenVertexArrays(1, &VAO_axes);
    glBindVertexArray(VAO_axes);
    glGenBuffers(1, &VBO_axes);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_axes), vertices_axes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };
    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    std::vector<std::string> faces {
        "Resources/right.jpg",
        "Resources/left.jpg",
        "Resources/top.jpg",
        "Resources/bottom.jpg",
        "Resources/front.jpg",
        "Resources/back.jpg"
    };
    cubemapTexture = loadCubemap(faces);
    isLoaded = true;
}

void SimpleGL3Window::update() {
    redraw();
}


int SimpleGL3Window::handle(int event) {
    static int first = 1;
    if (first && event == FL_SHOW && shown()) {
        first = 0;
        make_current();
        {
            GLenum err = glewInit();  // defines pters to functions of OpenGL V 1.2 and above
            glViewport(0, 0, screenWidth, screenHeight);
            glEnable(GL_DEPTH_TEST);
            if (err)
                Fl::warning("glewInit() failed returning %u", err);
            else
                std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
        }
        const uchar* glv = glGetString(GL_VERSION);
        std::cout << "GL_VERSION = " << glv << std::endl;
    }

    if (event == FL_MOVE){
        static bool firstMouse = true;
        static int lastX = 0;
        static int lastY = 0;
        auto xpos = Fl::event_x();
        auto ypos = Fl::event_y();

        if(firstMouse){
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
        lastX = xpos;
        lastY = ypos;
        camera.ProcessMouseMovement(xoffset, yoffset);
        firstMouse = false;
    } 

    if (event == FL_KEYUP){
        if (Fl::event_key() == 119){ // w
            wasd[0] = false;
        }
        if (Fl::event_key() == 115){ // s
            wasd[2] = false;
        }
        if (Fl::event_key() == 97){ // a
            wasd[1] = false;
        }
        if (Fl::event_key() == 100){ // d
            wasd[3] = false;
        }
    }

    if (event == FL_SHORTCUT){
        if (Fl::event_key() == 119){ // w
            wasd[0] = true;
        }
        if (Fl::event_key() == 115){ // s
            wasd[2] = true;
        }
        if (Fl::event_key() == 97){ // a
            wasd[1] = true;
        }
        if (Fl::event_key() == 100){ // d
            wasd[3] = true;
        }
    }
    redraw();
    return Fl_Gl_Window::handle(event);
}

unsigned int SimpleGL3Window::loadCubemap(const std::vector<std::string> &faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++){
        unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            SOIL_free_image_data(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureID;
}