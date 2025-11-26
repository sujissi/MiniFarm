#include "PCH.h"
#include "UI.h"
#include "Shader.h"


GLuint UI::s_VAO = 0;
GLuint UI::s_VBO = 0;
std::shared_ptr<Shader> UI::s_shader = nullptr;

void UI::Init()
{
	// Fullscreen quad vertices
	float vertices[] = {
		// pos        // uv
		0.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,   1.0f, 0.0f,
		1.0f, 1.0f,   1.0f, 1.0f,

		0.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 1.0f,   1.0f, 1.0f,
		0.0f, 1.0f,   0.0f, 1.0f,
	};

	glGenVertexArrays(1, &s_VAO);
	glGenBuffers(1, &s_VBO);

	glBindVertexArray(s_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, s_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// aPos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// aUV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	s_shader = std::make_shared<Shader>("Shaders/ui.vert", "Shaders/ui.frag");

	if (s_shader->GetID() == 0)
	{
		LOG_E("Text shader program is 0 (compile/link failed)");
	}
}

void UI::Draw(GLuint texture, const glm::vec2& posNDC, const glm::vec2& sizeNDC, const glm::vec4& color)
{
	if (!s_shader) return;

	s_shader->Use();
	s_shader->SetVec2(posNDC, "uPos");
	s_shader->SetVec2(sizeNDC, "uSize");
	s_shader->SetVec4(color, "uColor");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(s_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
