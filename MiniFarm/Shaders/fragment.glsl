#version 330 core

in vec3 vColor;
in vec2 vTextCoord;
in vec3 vNormal;
in vec3 vPos;

uniform int uDebugMode;
out vec4 FragColor;

uniform sampler2D atexture;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;

void main()
{
    if (uDebugMode == 1)
    {
        FragColor = vec4(vColor, 1.0);
    }
    else
    {
        // Base
        vec4 baseColor = texture(atexture, vTextCoord);

        // Diffuse 
        vec3 norm = normalize(vNormal);
        vec3 lightDir = normalize(uLightPos - vPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * uLightColor;
        
        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(uViewPos - vPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = specularStrength * spec * uLightColor;

        // Ambient
        float ambientStrength = 0.3;
        vec3 ambient = ambientStrength * uLightColor;
        
        // Result
        vec3 result = (diffuse + specular + ambient) * baseColor.rgb;
        FragColor = vec4(result, baseColor.a);
    }
}