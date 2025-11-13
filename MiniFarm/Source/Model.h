#pragma once

class Shader;

class Model
{
public:
	// 모델 생성자
    Model() = default;
	// 모델 생성자 (파일 경로)
    Model(const std::string& path);
	// 모델 소멸자
    ~Model();
	// 모델 그리기 함수
    void Draw();
private:
	// OBJ 파일 로드 함수
    void LoadOBJ(const std::string& path);
	// 모델 버퍼 설정 함수
    void SetupBuffers();
private:
	// 정점 구조체
    struct Vertex {
		glm::vec3 m_pos; // 위치
		glm::vec3 m_color; // 색상
		glm::vec3 m_normal; // 법선
		glm::vec3 m_uv; // UV 좌표
    };
	// 정점 리스트
    std::vector<Vertex> m_vertices;
	// 버텍스 배열 객체와 버텍스 버퍼 객체
    GLuint m_vao = 0, m_vbo = 0;
};
