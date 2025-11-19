#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(const glm::vec3& min, const glm::vec3& max);

	void UpdateTransform(const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rot) override;
	bool IntersectSegment(const glm::vec3& start, const glm::vec3& end,
		glm::vec3& hitPoint, float* outT) const override;
	virtual void DrawDebug() override;
public:
	glm::vec3 m_localMin;
	glm::vec3 m_localMax;

	glm::vec3 m_worldMin;
	glm::vec3 m_worldMax;
};
