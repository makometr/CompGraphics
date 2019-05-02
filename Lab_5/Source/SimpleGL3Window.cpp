#include "SimpleGL3Window.hpp"

SimpleGL3Window::SimpleGL3Window(int x, int y, int w, int h) :  Fl_Gl_Window(x, y, w, h) {
    mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
}

void SimpleGL3Window::draw(void) {
    shaderProgram.readAndCompile("Shaders/vertex.shader", "Shaders/fragment.shader");
    GLuint VBO_1, VBO_2, VAO_1, VAO_2;

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    GLfloat vertices_1[] = {
        // Позиции         // Цвета
        0.1f, 0.1f, 0.0f,  1.0f, 0.0f, 0.0f,   // Нижний правый угол
        0.5f, 0.9f, 0.0f,  0.0f, 1.0f, 0.0f,   // Нижний левый угол
        0.9f, 0.1f, 0.0f,  0.0f, 0.0f, 1.0f    // Верхний угол
    };
    GLfloat vertices_2[] = {
        -0.1f, -0.1f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.9f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.9f, -0.1f, 0.0f, 1.0f, 0.0f, 1.0f,
    }; 
    glGenVertexArrays(1, &VAO_1);
    glGenVertexArrays(1, &VAO_2);

    glGenBuffers(1, &VBO_1);
    glGenBuffers(1, &VBO_2);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO_1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
    // Атрибут с координатами
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Атрибут с цветом
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glBindVertexArray(VAO_2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
    // Атрибут с координатами
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Атрибут с цветом
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Game loop
        // Render
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
        shaderProgram.Use();
        glUniform1f(glGetUniformLocation(shaderProgram.Program, "delta"), 0.2f);

        glBindVertexArray(VAO_1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glBindVertexArray(VAO_2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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