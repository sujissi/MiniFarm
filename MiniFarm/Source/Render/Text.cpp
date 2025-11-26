#include "PCH.h"
#include "Text.h"
#include "Shader.h"
#include "TextureLoader.h"

void Text::Init(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    LOG("Text Init: %d x %d", screenWidth, screenHeight);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
        4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_shader = std::make_shared<Shader>("Shaders/text.vert", "Shaders/text.frag");

    if (m_shader->GetID() == 0)
    {
        LOG_E("Text shader program is 0 (compile/link failed)");
    }

    glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth,
        0.0f, (float)screenHeight);
    m_shader->Use();
    m_shader->SetProj(proj, "uProj");

    m_shader->SetTexture(0, "uFont");

    m_texture = TextureLoader::Load("font_atlas.png");
    LOG_D("Text::Init result - shaderID: %u, fontTex: %u",
        m_shader ? m_shader->GetID() : 0,
        m_texture);
}


void Text::Draw(const std::string& text,
    float x, float y,
    float scale,
    const glm::vec3& color)
{
    if (!m_shader || m_shader->GetID() == 0 || m_texture == 0)
    {
        LOG_E("Text::Draw aborted: shader or texture not ready");
        return;
    }

    if (text.empty())
        return;

    m_shader->Use();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint colorLoc = glGetUniformLocation(m_shader->GetID(), "uTextColor");
    glUniform3f(colorLoc, color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    const float glyphW = 16.0f;
    const float glyphH = 16.0f;
    float cellU = 1.0f / 16.0f;
    float cellV = 1.0f / 16.0f;

    for (char c : text)
    {
        unsigned char uc = static_cast<unsigned char>(c);
        int col = uc % 16;
        int rowTop = uc / 16;
        int row = 15 - rowTop;

        float uCellStart = col * cellU;
        float uCellEnd = (col + 1) * cellU;
        float trimU = cellU * m_trimRatioX;

        float u0 = uCellStart + trimU;
        float u1 = uCellEnd - trimU;

        float vCellStart = row * cellV;
        float vCellEnd = (row + 1) * cellV;
        float v0 = vCellStart;
        float v1 = vCellEnd;

        float baseWidth = glyphW * scale;
        float usedRatioX = 1.0f - (2.0f * m_trimRatioX);
        float w = baseWidth * usedRatioX;
        float h = glyphH * scale;

        float vertices[6][4] = {
            { x,     y,     u0, v0 },
            { x,     y + h, u0, v1 },
            { x + w, y + h, u1, v1 },

            { x,     y,     u0, v0 },
            { x + w, y + h, u1, v1 },
            { x + w, y,     u1, v0 }
        };

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        float advance = w + m_spacing; 
        x += advance;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

//  enterX, centerY : 기준이 될 중심 좌표 (픽셀 단위, Text::Init에서 설정한 스크린 기준)
// (0, 0) → 왼쪽 아래, y 커질수록 → 위쪽으로 올라감
void Text::DrawAt(const std::string& text, float centerX, float centerY, float scale, const glm::vec3& color)
{
    if (text.empty())
        return;

    const float glyphW = 16.0f;
    const float glyphH = 16.0f;

    float baseWidth = glyphW * scale;

    float usedRatioX = 1.0f - 2.0f * m_trimRatioX;
    float w = baseWidth * usedRatioX;
    float advance = w + m_spacing;

    float textWidth = (float)text.size() * advance - m_spacing;
    float textHeight = glyphH * scale;

    float x = centerX - textWidth * 0.5f;
    float y = centerY - textHeight * 0.5f;

    Draw(text, x, y, scale, color);
}