#include "PCH.h"
#include "Shader.h"
// 쉐이더 프로그램 ID
GLuint Shader::s_programID = 0;

// 쉐이더 초기화 함수
void Shader::Init(const char* vertexPath, const char* fragmentPath)
{
	LOG("Shader Init");

	std::string vertexSource = LoadFile(vertexPath);
	std::string fragmentSource = LoadFile(fragmentPath);

	GLuint vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

	s_programID = glCreateProgram();
	glAttachShader(s_programID, vertexShader);
	glAttachShader(s_programID, fragmentShader);
	glLinkProgram(s_programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	glGetProgramiv(s_programID, GL_LINK_STATUS, &success);

	if (!success) {
		GLchar log[512];
		glGetProgramInfoLog(s_programID, 512, nullptr, log);
		LOG_E("Shader link failed: %s", log);
		glDeleteProgram(s_programID);
		s_programID = 0;
	}
}

// 쉐이더 컴파일 함수
GLuint Shader::CompileShader(const std::string& source, GLenum type)
{
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		LOG_E("Shader compile failed (%s) : %s",
			(type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), log);

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}
// 모델 행렬 설정 함수
void Shader::SetModel(const glm::mat4& m_model, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(s_programID, name), 1, GL_FALSE, glm::value_ptr(m_model));
}
// 뷰 행렬 설정 함수
void Shader::SetView(const glm::mat4& view, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(s_programID, name), 1, GL_FALSE, glm::value_ptr(view));
}
// 투영 행렬 설정 함수
void Shader::SetProj(const glm::mat4& proj, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(s_programID, name), 1, GL_FALSE, glm::value_ptr(proj));
}
