#pragma once
class Shader
{
public:
	// 쉐이더 초기화 함수
	static void Init(const char* vertexPath, const char* fragmentPath);
	// 쉐이더 사용 함수
	static void Use() { glUseProgram(s_programID); }
	// 쉐이더 프로그램 ID 반환 함수
	static GLuint GetID() { return s_programID; }
	// 모델 행렬 설정 함수
	static void SetModel(const glm::mat4& m_model, const char* name = "uModel");
	// 뷰 행렬 설정 함수
	static void SetView(const glm::mat4& view, const char* name = "uView");
	// 투영 행렬 설정 함수
	static void SetProj(const glm::mat4& proj, const char* name = "uProj");

private:
	// 쉐이더 프로그램 ID
	static GLuint s_programID;
	// 쉐이더 프로그램 병합 함수
	static GLuint CompileShader(const std::string& source, GLenum type);
};
