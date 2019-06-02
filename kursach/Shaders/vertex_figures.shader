#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 figureColor;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(position, 1.0f);
    ourColor = figureColor;
}