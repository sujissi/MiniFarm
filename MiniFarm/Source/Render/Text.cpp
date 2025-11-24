#include "PCH.h"
#include "Text.h"
#include "Shader.h"
#include "stb_image.h"

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

    m_Shader = std::make_shared<Shader>("Shaders/text.vert", "Shaders/text.frag");

    if (m_Shader->GetID() == 0)
    {
        LOG_E("Text shader program is 0 (compile/link failed)");
    }

    glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth,
        0.0f, (float)screenHeight);
    m_Shader->Use();
    m_Shader->SetProj(proj, "uProj");

    m_Shader->SetTexture(0, "uFont");

    m_FontTexture = LoadFontAtlas("font_atlas.png");
    LOG_D("Text::Init result - shaderID: %u, fontTex: %u",
        m_Shader ? m_Shader->GetID() : 0,
        m_FontTexture);
}

GLuint Text::LoadFontAtlas(const std::string& path)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format;
        switch (nrChannels)
        {
        case 1: format = GL_RED;  break;
        case 3: format = GL_RGB;  break;
        case 4: format = GL_RGBA; break;
        default:
            LOG_E("Unsupported font texture format with %d channels", nrChannels);
            stbi_image_free(data);
            glDeleteTextures(1, &texture);
            return 0;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format,
            width, height, 0,
            format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        LOG("Font texture loaded: %s (%dx%d, channels: %d)",
            path.c_str(), width, height, nrChannels);
    }
    else
    {
        LOG_E("Failed to load font texture: %s", path.c_str());
        glDeleteTextures(1, &texture);
        texture = 0;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void Text::Draw(const std::string& text,
    float x, float y,
    float scale,
    const glm::vec3& color)
{
    if (!m_Shader || m_Shader->GetID() == 0 || m_FontTexture == 0)
    {
        LOG_E("Text::Draw aborted: shader or texture not ready");
        return;
    }

    if (text.empty())
        return;

    m_Shader->Use();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint colorLoc = glGetUniformLocation(m_Shader->GetID(), "uTextColor");
    glUniform3f(colorLoc, color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_FontTexture);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    const float glyphW = 16.0f;
    const float glyphH = 16.0f;

    for (char c : text)
    {
        unsigned char uc = static_cast<unsigned char>(c);
        int col = uc % 16;
        int row = uc / 16;
         row = 15 - row;

        float u0 = col / 16.0f;
        float v0 = row / 16.0f;
        float u1 = (col + 1) / 16.0f;
        float v1 = (row + 1) / 16.0f;

        float w = glyphW * scale;
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

        x += w;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void Text::DrawCentered(const std::string& text,
    float y,
    float scale,
    const glm::vec3& color)
{
    const float glyphW = 16.0f;
    float textWidth = (float)text.size() * glyphW * scale;
    float x = (m_screenWidth - textWidth) * 0.5f;
    Draw(text, x, y, scale, color);
}
