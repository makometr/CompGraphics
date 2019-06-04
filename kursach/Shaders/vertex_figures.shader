#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 aColor;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    Position = vec3(Position.x, 1.0 - Position.y, Position.z);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Color = aColor;
}