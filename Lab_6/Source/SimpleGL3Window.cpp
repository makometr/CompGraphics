#include "SimpleGL3Window.hpp"
#include "State.hpp"

SimpleGL3Window::SimpleGL3Window(State* ptr, int x, int y, int w, int h) :  Fl_Gl_Window(x, y, w, h) {
    statePtr = ptr; 
    mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
    screenWidth = this->w();
    screenHeight = this->h();
    this->when(FL_WHEN_CHANGED| FL_WHEN_ENTER_KEY_ALWAYS);
    this->callback([](Fl_Widget* widget){
        SimpleGL3Window* win = dynamic_cast<SimpleGL3Window*>(widget);
        if (win->changed()){
            std::cout << "EVEnT!\n";
            win->clear_changed();
        }
        else{
            std::cout << "Heh!";
        }
    });
}

void SimpleGL3Window::draw(void) {
    shaderProgramFigures.readAndCompile("Shaders/vertex_figures.shader", "Shaders/fragment.shader");
    shaderProgramAxes.readAndCompile("Shaders/vertex_axes.shader", "Shaders/fragment.shader");
    loadBuffers();
    Do_Movement();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(10.0f);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    shaderProgramFigures.Use();

    // Create transformations
    glm::mat4 model = glm::mat4(1.0f);
    auto [move_x, move_y, move_z] = statePtr->getXYZ(ActionType::translate);
    auto [angle_x, angle_y, angle_z] = statePtr->getXYZ(ActionType::rotate);
    auto [scale_x, scale_y, scale_z] = statePtr->getXYZ(ActionType::scale);
    model = glm::translate(model, glm::vec3(move_x, move_y, move_z));
    model = glm::rotate(model, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(angle_z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scale_x, scale_y, scale_z));

    glm::mat4 view = glm::mat4(1.0f);
    view = camera.GetViewMatrix();

    glm::mat4 projection = glm::mat4(1.0f);
    if (statePtr->getProjectionType() == ProjectionType::perspective){
        projection = glm::perspective(camera.Zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 50.0f);
    }
    if (statePtr->getProjectionType() == ProjectionType::orthogonal){
        projection = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, 0.1f, 100.0f );
    }
    // Get their uniform location ans Pass them to the shaders
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramFigures.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(shaderProgramFigures.Program, "figureColor"), 1.0, 1.0f, 1.0f);

    glLineWidth(2.0f); 
    glBindVertexArray(VAO_cube);
    glDrawElements(GL_LINES, 4*6, GL_UNSIGNED_INT, 0);

    glLineWidth(2.0f);
    glBindVertexArray(VAO_octahedra);
    glDrawElements(GL_LINES, 3*2*6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(5.0f);
    glLineStipple(1, 0x00FF);
    glUniform3f(glGetUniformLocation(shaderProgramFigures.Program, "figureColor"), 1.0, 0.0f, 0.0f);
    glBindVertexArray(VAO_octahedra);
    glDrawElements(GL_LINES, 3*2*6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDisable(GL_LINE_STIPPLE);

    glUniform3f(glGetUniformLocation(shaderProgramFigures.Program, "figureColor"), 0.0, 0.0f, 1.0f);
    glBindVertexArray(VAO_octahedra);
    glDrawElements(GL_POINTS, 3*2*6, GL_UNSIGNED_INT, 0);

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

int SimpleGL3Window::handle(int event) {
    int ret = Fl_Gl_Window::handle(event);
    std::cout << ret << std::endl;;
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
        std::cout << "Leave! " << Fl::event_x() << " " << Fl::event_y() << std::endl;
    }

    if (event == FL_MOVE){
        static bool firstMouse = true;
        static int lastX = 0;
        static int lastY = 0;
        auto xpos = Fl::event_x();
        auto ypos = Fl::event_y();
        std::cout << "Mouse move change: " << xpos << " " << ypos << std::endl;

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
        std::cout << "Up!\n";
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

    std::cout << "Event: " << event << std::endl;
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
        std::cout << "Pressed down  " << Fl::event_key() << std::endl;
    }
    redraw();
    return Fl_Gl_Window::handle(event);
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
    float vertices_cube[] = {
        // Coordinates
        -0.5,  0.5, 0.5, // N-W
         0.5,  0.5, 0.5, // N-E
         0.5, -0.5, 0.5, // S-E
        -0.5, -0.5, 0.5, // S-W

        -0.5,   0.5,  -0.5,   // N-W
         0.5,   0.5,  -0.5,   // N-E
         0.5,  -0.5,  -0.5,   // S-E
        -0.5,  -0.5,  -0.5,   // S-W
    };
    GLuint indices_cube[] = {
        0,1, 1,2, 2,3, 3,0,
        0,4, 4,5, 5,1,
        4,7, 7,6, 6,5,
        6,2, 7,3 
    };
    glGenVertexArrays(1, &VAO_cube);
    glGenBuffers(1, &VBO_cube);
    glGenBuffers(1, &EBO_cube);
    glBindVertexArray(VAO_cube);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cube);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_cube), indices_cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);




    float vertices_octahedra[] = {
        // Coordinates
         0.0,  0.5,  0.0,
         0.0, -0.5,  0.0,  
         0.0,  0.0, -0.5,
        -0.5,  0.0,  0.0,
         0.0,  0.0,  0.5,
         0.5,  0.0,  0.0,  
    };
    GLuint indices_octahedra[] = {
        0,2, 0,3, 0,4, 0,5,
        1,2, 1,3, 1,4, 1,5,
        2,3, 3,4, 4,5, 5,2
    };
    glGenVertexArrays(1, &VAO_octahedra);
    glGenBuffers(1, &VBO_octahedra);
    glGenBuffers(1, &EBO_octahedra);
    glBindVertexArray(VAO_octahedra);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_octahedra);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_octahedra), vertices_octahedra, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_octahedra);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_octahedra), indices_octahedra, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
}

void SimpleGL3Window::update() {
    redraw();
}