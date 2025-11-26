#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
    vec4 texColor = texture(uTexture, TexCoords);
    FragColor = texColor * uColor;
}
