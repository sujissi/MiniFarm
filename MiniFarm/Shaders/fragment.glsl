#version 330 core

in vec3 vColor;
in vec2 vTextCoord;

uniform int uDebugMode;
out vec4 FragColor;

uniform sampler2D atexture;

void main()
{
    if (uDebugMode == 1)
    {
        FragColor = vec4(vColor, 1.0);
    }
    else
    {
        FragColor = texture(atexture, vTextCoord);
    }
}