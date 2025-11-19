#pragma once
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

inline glm::mat4 Translate(const glm::vec3& t)
{
	return glm::translate(glm::mat4(1.0f), t);
}

inline glm::mat4 Rotate(float deg, const glm::vec3& axis)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(deg), axis);
}

inline glm::mat4 Scale(const glm::vec3& s)
{
	return glm::scale(glm::mat4(1.0f), s);
}

inline glm::mat4 PivotRotate(float deg, const glm::vec3& axis, const glm::vec3& pivot)
{
	return glm::translate(glm::mat4(1), pivot)
		* glm::rotate(glm::mat4(1), glm::radians(deg), axis)
		* glm::translate(glm::mat4(1), -pivot);
}

inline glm::mat4 PivotScale(float s, const glm::vec3& pivot)
{
	return glm::translate(glm::mat4(1), pivot)
		* glm::scale(glm::mat4(1), glm::vec3(s))
		* glm::translate(glm::mat4(1), -pivot);
}

inline bool IntersectSegmentAABB(const glm::vec3& start, const glm::vec3& end,
    const glm::vec3& aabbMin, const glm::vec3& aabbMax, float& outT, glm::vec3& outPoint)
{
    glm::vec3 dir = end - start;
    glm::vec3 invDir = 1.0f / dir;

    float tMin = 0.0f;
    float tMax = 1.0f;  // segment range is 0~1

    for (int i = 0; i < 3; i++)
    {
        float t1 = (aabbMin[i] - start[i]) * invDir[i];
        float t2 = (aabbMax[i] - start[i]) * invDir[i];

        float tNear = glm::min(t1, t2);
        float tFar = glm::max(t1, t2);

        tMin = glm::max(tMin, tNear);
        tMax = glm::min(tMax, tFar);

        if (tMax < tMin)
            return false; // no collision
    }

    outT = tMin;
    outPoint = start + dir * tMin;
    return true;
}