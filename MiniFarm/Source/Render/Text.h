#pragma once
#include "Shader.h"

class Text
{
public:
    void Init(int screenWidth, int screenHeight);
    void Draw(const std::string& text,
        float x, float y,
        float scale,
        const glm::vec3& color);

    void DrawCentered(const std::string& text,
        float y,
        float scale,
        const glm::vec3& color);

private:
    GLuint LoadFontAtlas(const std::string& path);

private:
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_FontTexture = 0;
    std::shared_ptr<Shader> m_Shader;

    int m_screenWidth = 0;
    int m_screenHeight = 0;
};