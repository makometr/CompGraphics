#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform vec2 mousePos;
uniform sampler2D ourTexture;
uniform float fadeDistance;

float getDistance(vec2 p1, vec2 p2) {
	return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}

float getLightIntensity() {
	float dist = getDistance(gl_FragCoord.xy, mousePos);
	return fadeDistance / dist;
}

void main()
{
    color = texture(ourTexture, TexCoord) * getLightIntensity();
}