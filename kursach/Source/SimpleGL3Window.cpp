#include "SimpleGL3Window.hpp"
#include "State.hpp"

SimpleGL3Window::SimpleGL3Window(State* ptr, int x, int y, int w, int h) :  Fl_Gl_Window(x, y, w, h){
    statePtr = ptr; 
    mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
    screenWidth = this->w();
    screenHeight = this->h();
}

void SimpleGL3Window::draw(void) {
    shaderProgramFigures.readAndCompile("Shaders/vertex_figures.shader", "Shaders/fragment.shader");
    shaderProgramAxes.readAndCompile("Shaders/vertex_axes.shader", "Shaders/fragment.shader");
    loadBuffers();
    Do_Movement();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Create transformations
    // auto [move_x, move_y, move_z] = statePtr->getXYZ(ActionType::translate);
    // auto [angle_x, angle_y, angle_z] = statePtr->getXYZ(ActionType::rotate);
    // auto [scale_x, scale_y, scale_z] = statePtr->getXYZ(ActionType::scale);
    // model = glm::translate(model, glm::vec3(move_x, move_y, move_z));
    // model = glm::rotate(model, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(angle_z), glm::vec3(0.0f, 0.0f, 1.0f));
    // model = glm::scale(model, glm::vec3(scale_x, scale_y, scale_z));


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.4f, 0.0f));
    model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
    glm::mat4 view = glm::mat4(1.0f);
    view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(camera.Zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 50.0f);
    shaderProgramFigures.Use();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shaderProgramFigures.Program, "figureColor"), 1.0, 1.0f, 1.0f);
    shape_1.draw();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.1f, 0.7f, 0.0f));
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    shape_2.draw();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-2.1f, 0.7f, 0.0f));
    model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    shape_3.draw();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, 2.6f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    shape_4.draw();
    

    // axes
    shaderProgramAxes.Use();
    glm::mat4 modelAxe = glm::mat4(1.0f);
    modelAxe = glm::scale(modelAxe, glm::vec3(100, 100, 100));

    glm::mat4 viewAxe = glm::mat4(1.0f);
    viewAxe = camera.GetViewMatrix();

    glm::mat4 projectionAxe = glm::mat4(1.0f);
    if (statePtr->getProjectionType() == ProjectionType::perspective){
        projectionAxe = glm::perspective(camera.Zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 50.0f);
    }
    if (statePtr->getProjectionType() == ProjectionType::orthogonal){
        projectionAxe = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f );
    }
    // Get their uniform location ans Pass them to the shaders
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramAxes.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelAxe));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramAxes.Program, "view"), 1, GL_FALSE, glm::value_ptr(viewAxe));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramAxes.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionAxe));

    glBindVertexArray(VAO_axes);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 6*3);
    glBindVertexArray(0);

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

    if (event == FL_LEAVE){
        // std::cout << "Leave! " << Fl::event_x() << " " << Fl::event_y() << std::endl;
    }

    if (event == FL_MOVE){
        static bool firstMouse = true;
        static int lastX = 0;
        static int lastY = 0;
        auto xpos = Fl::event_x();
        auto ypos = Fl::event_y();
        // std::cout << "Mouse move change: " << xpos << " " << ypos << std::endl;

        if(firstMouse)
        {
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
        // std::cout << "Up!\n";
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

    // std::cout << "Event: " << event << std::endl;
    if (event == FL_SHORTCUT){
        if (Fl::event_key() == 119){ // w
            // camera.ProcessKeyboard(FORWARD);
            wasd[0] = true;
        }
        if (Fl::event_key() == 115){ // s
            // camera.ProcessKeyboard(BACKWARD);
            wasd[2] = true;
        }
        if (Fl::event_key() == 97){ // a
            // camera.ProcessKeyboard(LEFT);
            wasd[1] = true;
        }
        if (Fl::event_key() == 100){ // d
            // camera.ProcessKeyboard(RIGHT);
            wasd[3] = true;
        }
        // std::cout << "Pressed down  " << Fl::event_key() << std::endl;
    }
    redraw();
    return Fl_Gl_Window::handle(event);
}