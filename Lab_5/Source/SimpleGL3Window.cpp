#include "SimpleGL3Window.hpp"

SimpleGL3Window::SimpleGL3Window(int x, int y, int w, int h) :  Fl_Gl_Window(x, y, w, h) {
    mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
    texturePNG = new Fl_PNG_Image("texture.png");
    if (texturePNG->fail()){
        std::cout << "ERROR::TEXTURE::LOAD_FROM_FILE\n";
    }
}

void SimpleGL3Window::draw(void) {
    shaderProgram.readAndCompile("Shaders/vertex.shader", "Shaders/fragment.shader");

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO


    // Load and create a texture 
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image("texture.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    add_output("Size of image: %d x %d\n", width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Activate shader
        shaderProgram.Use();       
        
        // Draw container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    // return SimpleGL3Window::draw();
}

int SimpleGL3Window::handle(int event) {
    static int first = 1;
    if (first && event == FL_SHOW && shown()) {
        first = 0;
        make_current();
        {
            GLenum err = glewInit();  // defines pters to functions of OpenGL V 1.2 and above
            if (err)
                Fl::warning("glewInit() failed returning %u", err);
            else
                add_output("Using GLEW %s\n", glewGetString(GLEW_VERSION));
        }
        const uchar* glv = glGetString(GL_VERSION);
        add_output("GL_VERSION = %s\n", glv);
        sscanf((const char*)glv, "%d", &gl_version_major);
    }

    if (event == FL_MOVE){
        auto x = Fl::event_x();
        auto y = Fl::event_y();
        glUniform2f(glGetUniformLocation(shaderProgram.Program, "mousePos"), x, y-1);
        redraw();
    }

    if (event == FL_PUSH && gl_version_major >= 3) {
        static float factor = 1.1;
        GLfloat data[4];
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(GLfloat), data);
        if (data[0] < -0.88 || data[0] > -0.5)
            factor = 1 / factor;
        data[0] *= factor;
        glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(GLfloat), data);
        glGetBufferSubData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat),
                            4 * sizeof(GLfloat), data);
        data[0] *= factor;
        glBufferSubData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), 4 * sizeof(GLfloat),
                        data);
        redraw();
        add_output("push Fl_Gl_Window::pixels_per_unit()=%.1f\n",
                    pixels_per_unit());
        return 1;
    }
    return Fl_Gl_Window::handle(event);
}

void SimpleGL3Window::reset(void) {
    // shaderProgram = 0;
}