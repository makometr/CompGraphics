#version 430 core

in vec3 vPosition;
// in vec3 vColor;

// out vec3 fColor;

void main()
{
	// fColor = vColor;
	gl_Position = vec4(vPosition, 1.0f);
}
