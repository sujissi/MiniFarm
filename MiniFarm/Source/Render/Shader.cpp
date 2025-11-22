#include "PCH.h"
#include "Shader.h"

GLuint Shader::s_programID = 0;

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

void Shader::SetModel(const glm::mat4& m_model, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(s_programID, name), 1, GL_FALSE, &m_model[0][0]);
}

void Shader::SetView(const glm::mat4& view, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(s_programID, name), 1, GL_FALSE, &view[0][0]);
}

void Shader::SetProj(const glm::mat4& proj, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(s_programID, name), 1, GL_FALSE, &proj[0][0]);
}

void Shader::SetTexture(GLint textureUnit, const char* name)
{
	glUniform1i(glGetUniformLocation(s_programID, name), textureUnit);
}

void Shader::BeginDebugDraw(const glm::vec3& color)
{
	Use();
	SetModel(glm::mat4(1.0f));
	glUniform1i(glGetUniformLocation(s_programID, "uDebugMode"), 1);
	glUniform3f(glGetUniformLocation(s_programID, "uDebugColor"), color.x, color.y, color.z);
}

void Shader::EndDebugDraw()
{
	glUniform1i(glGetUniformLocation(s_programID, "uDebugMode"), 0);
}

void Shader::SetLightPos(const glm::vec3& pos, const char* name)
{
	glUniform3f(glGetUniformLocation(s_programID, name), pos.x, pos.y, pos.z);
}

void Shader::SetLightColor(const glm::vec3& color, const char* name)
{
	glUniform3f(glGetUniformLocation(s_programID, name), color.x, color.y, color.z);
}

void Shader::SetViewPos(const glm::vec3& pos, const char* name)
{
	glUniform3f(glGetUniformLocation(s_programID, name), pos.x, pos.y, pos.z);
}