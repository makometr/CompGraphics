#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 Color;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    vec3 I = normalize(cameraPos - Position);
    vec3 R = reflect(-I, normalize(Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
    FragColor = vec4(FragColor.r + Color.r/255, FragColor.g + Color.g/255, FragColor.b + Color.b/255, 1.0);
    // FragColor = vec4(normalize(Normal), 1.0f);
}