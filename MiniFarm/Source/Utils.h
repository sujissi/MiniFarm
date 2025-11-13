#pragma once

// 파일 로드 검사 함수
inline std::string LoadFile(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}
// 이동 행렬 생성 함수
inline glm::mat4 Translate(const glm::vec3& t)
{
	return glm::translate(glm::mat4(1.0f), t);
}
// 회전 행렬 생성 함수
inline glm::mat4 Rotate(float deg, const glm::vec3& axis)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(deg), axis);
}
// 크기 조절 행렬 생성 함수
inline glm::mat4 Scale(const glm::vec3& s)
{
	return glm::scale(glm::mat4(1.0f), s);
}
// 자신을 중심으로 회전 행렬 생성 함수
inline glm::mat4 PivotRotate(float deg, const glm::vec3& axis, const glm::vec3& pivot)
{
	return glm::translate(glm::mat4(1), pivot)
		* glm::rotate(glm::mat4(1), glm::radians(deg), axis)
		* glm::translate(glm::mat4(1), -pivot);
}
// 자신을 중심으로 크기 조절 행렬 생성 함수
inline glm::mat4 PivotScale(float s, const glm::vec3& pivot)
{
	return glm::translate(glm::mat4(1), pivot)
		* glm::scale(glm::mat4(1), glm::vec3(s))
		* glm::translate(glm::mat4(1), -pivot);
}