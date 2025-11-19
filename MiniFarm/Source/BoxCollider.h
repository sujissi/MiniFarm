#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:
	glm::vec3 localMin;
	glm::vec3 localMax;

	glm::vec3 worldMin;
	glm::vec3 worldMax;

public:
	BoxCollider(const glm::vec3& min, const glm::vec3& max);

	void UpdateTransform(const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rot) override;
	bool IntersectSegment(const glm::vec3& start, const glm::vec3& end,
		glm::vec3& hitPoint, float* outT) const override;

	void DrawDebug() override;
};
