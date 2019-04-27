#include "SimpleGL3Window.hpp"

SimpleGL3Window::SimpleGL3Window(int x, int y, int w, int h) :  Fl_Gl_Window(x, y, w, h) {
    mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
    shaderProgram = 0;
}

void SimpleGL3Window::draw(void) {
    if (gl_version_major < 3)
        return;
    if (!shaderProgram) {
        GLuint vs;
        GLuint fs;
        int Mslv, mslv;  // major and minor version numbers of the shading language
        sscanf((char*)glGetString(GL_SHADING_LANGUAGE_VERSION), "%d.%d", &Mslv, &mslv);
        add_output("Shading Language Version=%d.%d\n", Mslv, mslv);

        const char* vss_format =
            "#version %d%d\n\
            uniform vec2 p;\
            in vec4 position;\
            in vec4 colour;\
            out vec4 colourV;\
            void main (void){ \
                colourV = colour;\
                gl_Position = vec4(p, 0.0, 0.0) + position;\
            }";
        
        char vss_string[300];
        const char* vss = vss_string;
        sprintf(vss_string, vss_format, Mslv, mslv);
        const char* fss_format =
            "#version %d%d\n\
            in vec4 colourV;\
            out vec4 fragColour;\
            void main(void) {\
                fragColour = colourV;\
            }";
        
        char fss_string[200];
        const char* fss = fss_string;
        sprintf(fss_string, fss_format, Mslv, mslv);
        GLint err;
        GLchar CLOG[1000];
        GLsizei length;
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vss, NULL);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &err);

        if (err != GL_TRUE) {
            glGetShaderInfoLog(vs, sizeof(CLOG), &length, CLOG);
            add_output("vs ShaderInfoLog=%s\n", CLOG);
        }
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fss, NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &err);

        if (err != GL_TRUE) {
            glGetShaderInfoLog(fs, sizeof(CLOG), &length, CLOG);
            add_output("fs ShaderInfoLog=%s\n", CLOG);
        }
        // Attach the shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vs);
        glAttachShader(shaderProgram, fs);
        glBindFragDataLocation(shaderProgram, 0, "fragColour");
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &err);
        if (err != GL_TRUE) {
            glGetProgramInfoLog(shaderProgram, sizeof(CLOG), &length, CLOG);
            add_output("link log=%s\n", CLOG);
        }
        // Get pointers to uniforms and attributes
        positionUniform = glGetUniformLocation(shaderProgram, "p");
        colourAttribute = glGetAttribLocation(shaderProgram, "colour");
        positionAttribute = glGetAttribLocation(shaderProgram, "position");
        glDeleteShader(vs);
        glDeleteShader(fs);
        // Upload vertices (1st four values in a row) and colours (following four
        // values)
        GLfloat vertexData[] = {-0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
                                -0.5, 0.5,  0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
                                0.5,  0.5,  0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
                                0.5,  -0.5, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * 8 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

        glEnableVertexAttribArray((GLuint)positionAttribute);
        glEnableVertexAttribArray((GLuint)colourAttribute);
        glVertexAttribPointer((GLuint)positionAttribute, 4, GL_FLOAT, GL_FALSE,
                            8 * sizeof(GLfloat), 0);
        glVertexAttribPointer((GLuint)colourAttribute, 4, GL_FLOAT, GL_FALSE,
                            8 * sizeof(GLfloat), (char*)0 + 4 * sizeof(GLfloat));
    }
    else if ((!valid())) {
        glViewport(0, 0, pixel_w(), pixel_h());
    }
    glClearColor(0.08, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    GLfloat p[] = {0, 0};
    glUniform2fv(positionUniform, 1, (const GLfloat*)&p);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
        add_output("push  Fl_Gl_Window::pixels_per_unit()=%.1f\n",
                    pixels_per_unit());
        return 1;
    }
    return Fl_Gl_Window::handle(event);
}

void SimpleGL3Window::reset(void) {
    shaderProgram = 0;
}