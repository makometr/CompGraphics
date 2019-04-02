#version 330 core

uniform vec2 mousePos;
uniform sampler2D texture2D;

in vec2 fTexCoord;

out vec4 outColor;

const float lightRadius  = 30.0f,
            fadeDistance = 30.0f;

float getDistance(vec2 p1, vec2 p2) {
	return sqrt(pow(p1.x-p2.x, 2)+pow(p1.y-p2.y, 2));
}
float getLightIntensity() {
	float dist = getDistance(gl_FragCoord.xy, mousePos);
	if (dist <= lightRadius) {
		return 1.0f;
	}
	return fadeDistance/(dist-lightRadius);
}

void main()
{
	outColor = texture(texture2D, fTexCoord) * getLightIntensity();
}
