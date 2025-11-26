#pragma once
#include "TextureLoader.h"

class Shader;
class UIRenderer
{
public:
    static void Init();
    static void Draw(const TextureInfo& textureInfo, const glm::vec2& posNDC, float size, const glm::vec4& color = glm::vec4(1.0f));

private:
    static GLuint s_VAO, s_VBO;
    static std::shared_ptr<Shader> s_shader;
};
