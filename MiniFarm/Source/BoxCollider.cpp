#include "PCH.h"
#include "BoxCollider.h"
#include "Shader.h"
#include "DebugDrawer.h"

BoxCollider::BoxCollider(const glm::vec3& min, const glm::vec3& max)
    : m_localMin(min), m_localMax(max)
{
    m_worldMin = min;
    m_worldMax = max;
}

void BoxCollider::UpdateTransform(const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rot)
{
    glm::vec3 half = (m_localMax - m_localMin) * 0.5f * scale;
    glm::vec3 center = (m_localMax + m_localMin) * 0.5f;

    glm::vec3 worldCenter = center * scale + pos;

    m_worldMin = worldCenter - half;
    m_worldMax = worldCenter + half;
}

bool BoxCollider::IntersectSegment(const glm::vec3& start, const glm::vec3& end, glm::vec3& hitPoint, float* outT) const
{
    float t;
    if (!IntersectSegmentAABB(start, end, m_worldMin, m_worldMax, t, hitPoint))
        return false;

    if (outT) *outT = t;
    return true;
}

void BoxCollider::DrawDebug()
{
    DebugDrawer::DrawBox(m_worldMin, m_worldMax, glm::vec3(1, 0, 0));
}
