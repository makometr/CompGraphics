#version 330 core
in vec4 vertexColor; // Входная переменная из вершинного шейдера (то же название и тот же тип)

out vec4 color;

void main()
{
    color = vertexColor;
} 