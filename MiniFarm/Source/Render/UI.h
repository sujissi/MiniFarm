#pragma once

class Shader;
class UI
{
public:
    static void Init();
    static void Draw(GLuint texture, const glm::vec2& posNDC, const glm::vec2& sizeNDC, const glm::vec4& color);

private:
    static GLuint s_VAO, s_VBO;
    static std::shared_ptr<Shader> s_shader;
};
