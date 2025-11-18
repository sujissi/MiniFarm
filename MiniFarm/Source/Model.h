#pragma once

class Shader;

class Model
{
public:
	Model() = default;
	Model(const std::string& path, const std::string& texturePath);
	~Model();

	void Draw();
private:
	void LoadOBJ(const std::string& path);
	GLuint LoadIMG(const std::string& path);
	void SetupBuffers();
private:
	struct Vertex {
		glm::vec3 m_pos;
		glm::vec3 m_color;
		glm::vec3 m_normal;
		glm::vec2 m_uv;
	};
 
	std::vector<Vertex> m_vertices;
	GLuint m_vao = 0, m_vbo = 0;
	GLuint m_textureID = 0;
};
