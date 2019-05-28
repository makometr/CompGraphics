#pragma once
#include "libs.hpp"

class Shader {
public:
    GLuint Program = 0; // Идентификатор программы

public:
    Shader() = default;
    void readAndCompile(const GLchar* vertexPath, const GLchar* fragmentPath);

    bool isLoaded();
    void Use();
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(Program, name.c_str()), value); 
    }
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};