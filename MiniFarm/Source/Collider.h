#pragma once
class Collider
{
public:
	virtual ~Collider() = default;

	virtual bool Intersects(const Collider* other) const = 0;
	virtual bool IntersectSegment(const glm::vec3& start, const glm::vec3& end,
		glm::vec3& hitPoint, float* outT = nullptr) const = 0;
	virtual void InitTransform(const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rot) = 0;
	virtual void UpdatePos(const glm::vec3& pos) = 0;
	virtual void DrawDebug() {}
};
