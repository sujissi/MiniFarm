#version 330 core

in vec3 vColor;
in vec2 vTextCoord;

out vec4 FragColor;

uniform sampler2D texture;

void main()
{
    FragColor = texture2D(texture, vTextCoord);
    //FragColor = vec4(vColor, 1.0);
}