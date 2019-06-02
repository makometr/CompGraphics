#version 330 core
in vec3 ourColor;
out vec4 FragColor;

out vec4 color;
in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
	// color = vec4(ourColor, 1.0f);
	color = texture(texture1, TexCoords);
}