#pragma once
class Shader
{
public:
	static void Init(const char* vertexPath, const char* fragmentPath);
	static void Use() { glUseProgram(s_programID); }
	static GLuint GetID() { return s_programID; }

	static void SetModel(const glm::mat4& m_model, const char* name = "uModel");
	static void SetView(const glm::mat4& view, const char* name = "uView");
	static void SetProj(const glm::mat4& proj, const char* name = "uProj");
	static void SetTexture(GLint textureUnit, const char* name = "atexture");

	static void SetLightPos(const glm::vec3& pos, const char* name = "uLightPos");
	static void SetLightColor(const glm::vec3& color, const char* name = "uLightColor");
	static void SetViewPos(const glm::vec3& pos, const char* name = "uViewPos");
	
	static void BeginDebugDraw(const glm::vec3& color);
	static void EndDebugDraw();
private:
	static GLuint s_programID;
	static GLuint CompileShader(const std::string& source, GLenum type);
};
