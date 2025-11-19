#include "PCH.h"
#include "Model.h"
#include "Shader.h"
// STB 이미지 로더 포함
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(const std::string& name)
	:Model(name + ".obj", name + ".png")
{
	LOG("Model loaded. Vertex Count = %d", (int)m_vertices.size());
}

Model::Model(const std::string& path, const std::string& texturePath)
{
	LOG("%s", path.c_str());
	LoadOBJ(path);
	m_textureID = LoadIMG(texturePath);	
	LOG("Model loaded. Vertex Count = %d", (int)m_vertices.size());
}

Model::~Model()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	
	if (m_textureID != 0) {
		glDeleteTextures(1, &m_textureID);
	}
}

void Model::LoadOBJ(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		LOG_E("Failed to load OBJ : %s", path.c_str());
		return;
	}

	std::vector<glm::vec3> tempPos;
	std::vector<glm::vec3> tempNorm;
	std::vector<glm::vec2> tempTex;
	std::string line;
	int faceCount = 0;

	while (getline(file, line)) {
		std::stringstream ss(line);
		std::string type; ss >> type;

		if (type == "v") {
			glm::vec3 p;
			ss >> p.x >> p.y >> p.z;
			tempPos.push_back(p);
		}
		else if (type == "vn") {
			glm::vec3 n;
			ss >> n.x >> n.y >> n.z;
			tempNorm.push_back(n);
		}
		else if (type == "vt") {
			glm::vec2 uv;
			ss >> uv.x >> uv.y;
			tempTex.push_back(uv);
		}
		else if (type == "f") {
			std::string vertex_str;
			std::vector<std::vector<unsigned int>> face_indices;
			while (ss >> vertex_str) {
				std::vector<unsigned int> indices = { 0, 0, 0 }; // v, vt, vn
				size_t pos1 = vertex_str.find('/');
				if (pos1 != std::string::npos) {
					indices[0] = std::stoul(vertex_str.substr(0, pos1));
					size_t pos2 = vertex_str.find('/', pos1 + 1);
					if (pos2 != std::string::npos) {
						if (pos2 - pos1 > 1) indices[1] = std::stoul(vertex_str.substr(pos1 + 1, pos2 - pos1 - 1));
						indices[2] = std::stoul(vertex_str.substr(pos2 + 1));
					}
					else {
						if (vertex_str.length() > pos1 + 1) indices[1] = std::stoul(vertex_str.substr(pos1 + 1));
					}
				}
				else indices[0] = std::stoul(vertex_str);
				
				if (indices[0] > 0) indices[0]--;
				if (indices[1] > 0) indices[1]--;
				if (indices[2] > 0) indices[2]--;
				face_indices.push_back(indices);
			}


			// 면이 삼각형인 경우
			if (face_indices.size() == 3) {
				for (const auto& indies : face_indices) {
					Vertex vertex{};
					vertex.m_pos = tempPos[indies[0]];
					vertex.m_normal = tempNorm.size() > indies[2] ? tempNorm[indies[2]] : glm::vec3(0.0f, 1.0f, 0.0f);
					vertex.m_uv = tempTex.size() > indies[1] ? tempTex[indies[1]] : glm::vec2(0.0f, 0.0f);
					m_vertices.push_back(vertex);
				}
			}
			// 면이 사각형인 경우 두 개의 삼각형으로 분할
			else if (face_indices.size() == 4) {
				// 첫 번째 삼각형: 0, 1, 2
				for (int i : {0, 1, 2}) {
					Vertex vertex{};
					vertex.m_pos = tempPos[face_indices[i][0]];
					vertex.m_normal = tempNorm.size() > face_indices[i][2] ? tempNorm[face_indices[i][2]] : glm::vec3(0.0f, 1.0f, 0.0f);
					vertex.m_uv = tempTex.size() > face_indices[i][1] ? tempTex[face_indices[i][1]] : glm::vec2(0.0f, 0.0f);
					m_vertices.push_back(vertex);
				}
				// 두 번째 삼각형: 0, 2, 3
				for (int i : {0, 2, 3}) {
					Vertex vertex{};
					vertex.m_pos = tempPos[face_indices[i][0]];
					vertex.m_normal = tempNorm.size() > face_indices[i][2] ? tempNorm[face_indices[i][2]] : glm::vec3(0.0f, 1.0f, 0.0f);
					vertex.m_uv = tempTex.size() > face_indices[i][1] ? tempTex[face_indices[i][1]] : glm::vec2(0.0f, 0.0f);
					m_vertices.push_back(vertex);
				}
			}
			
			faceCount++;
		}
	}
	SetupBuffers();
	InitBounds();
}

GLuint Model::LoadIMG(const std::string& path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// 텍스처 파라미터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 이미지 로드
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // OpenGL은 Y축이 뒤집어져 있음
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		GLenum format;
		switch (nrChannels) {
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				LOG_E("Unsupported texture format with %d channels", nrChannels);
				stbi_image_free(data);
				glDeleteTextures(1, &texture);
				return 0;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		LOG("Texture loaded successfully: %s (%dx%d, channels: %d)", path.c_str(), width, height, nrChannels);
	}
	else {
		LOG_E("Failed to load texture: %s", path.c_str());
		glDeleteTextures(1, &texture);
		texture = 0;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0); // 텍스처 바인딩 해제
	return texture;
}

void Model::SetupBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER,
		m_vertices.size() * sizeof(Vertex),
		m_vertices.data(),
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Model::InitBounds()
{
	// AABB 계산
	if (!m_vertices.empty())
	{
		m_minBounds = m_vertices[0].m_pos;
		m_maxBounds = m_vertices[0].m_pos;

		for (auto& v : m_vertices)
		{
			m_minBounds.x = std::min(m_minBounds.x, v.m_pos.x);
			m_minBounds.y = std::min(m_minBounds.y, v.m_pos.y);
			m_minBounds.z = std::min(m_minBounds.z, v.m_pos.z);

			m_maxBounds.x = std::max(m_maxBounds.x, v.m_pos.x);
			m_maxBounds.y = std::max(m_maxBounds.y, v.m_pos.y);
			m_maxBounds.z = std::max(m_maxBounds.z, v.m_pos.z);
		}
	}

}

void Model::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glBindVertexArray(0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}
