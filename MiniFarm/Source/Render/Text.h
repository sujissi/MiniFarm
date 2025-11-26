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

	void DrawAt(const std::string& text, float centerX, float centerY, float scale, const glm::vec3& color);
	void SetSpacing(float s) { m_spacing = s; }

private:
	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	GLuint m_texture = 0;
	std::shared_ptr<Shader> m_shader;

	int m_screenWidth = 0;
	int m_screenHeight = 0;

	const float m_trimRatioX = 0.3f;// 글자 좌우 여백 자르기 비율
	float m_spacing = 0.0f;

};