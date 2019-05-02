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
};