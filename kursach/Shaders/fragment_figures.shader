#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    vec3 I = normalize(cameraPos - Position);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
    FragColor = vec4(FragColor.r+0.5, FragColor.g, FragColor.b, 1.0);
    // FragColor = vec4(normalize(Normal), 1.0f);
}