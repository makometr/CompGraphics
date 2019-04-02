#version 330 core

in vec3 vPosition;
in vec2 vTexCoord;

out vec2 fTexCoord;

void main() {
	fTexCoord = vTexCoord;
	gl_Position = vec4(vPosition, 1.0);
}
