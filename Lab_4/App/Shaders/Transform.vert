#version 430 core

in vec2 vPosition;

out vec4 fColor;

uniform mat4 trans;

void main()
{
	fColor = vec4(0.8f, 0.5f, 0.5f, 1.0f);
	gl_Position = trans * vec4(vPosition, 1.0f, 1.0f);
}
