#include "PCH.h"
#include "Model.h"
#include "Shader.h"

Model::Model(const std::string& path)
{
    LOG("%s", path.c_str());
    LoadOBJ(path);
    LOG("Model loaded. Vertex Count = %d", (int)m_vertices.size());
}

Model::~Model()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void Model::LoadOBJ(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG_E("Failed to load OBJ : % s", path.c_str());
        return;
    }

    std::vector<glm::vec3> tempPos;
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
        else if (type == "f") {
            int a, b, c;
            ss >> a >> b >> c;
            faceCount++;

            glm::vec3 m_color{
                float(rand() % 100) / 100.0f,
                float(rand() % 100) / 100.0f,
                float(rand() % 100) / 100.0f
            };

            m_vertices.push_back({ tempPos[a - 1], m_color });
            m_vertices.push_back({ tempPos[b - 1], m_color });
            m_vertices.push_back({ tempPos[c - 1], m_color });
        }
    }
    SetupBuffers();
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

    glBindVertexArray(0);
}

void Model::Draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
}
