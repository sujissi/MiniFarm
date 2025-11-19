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

void BoxCollider::UpdateTransform(const glm::vec3& pos,
    const glm::vec3& scale,
    const glm::vec3& rot)
{
    glm::vec3 localCenter = (m_localMax + m_localMin) * 0.5f;
    glm::vec3 localHalf = (m_localMax - m_localMin) * 0.5f * scale;

    glm::mat4 R = glm::yawPitchRoll(
        glm::radians(rot.y),
        glm::radians(rot.x),
        glm::radians(rot.z)
    );

    glm::mat3 rotMat = glm::mat3(R);

    glm::vec3 corners[8] = {
        localCenter + glm::vec3(-localHalf.x, -localHalf.y, -localHalf.z),
        localCenter + glm::vec3(localHalf.x, -localHalf.y, -localHalf.z),
        localCenter + glm::vec3(localHalf.x, -localHalf.y,  localHalf.z),
        localCenter + glm::vec3(-localHalf.x, -localHalf.y,  localHalf.z),
        localCenter + glm::vec3(-localHalf.x,  localHalf.y, -localHalf.z),
        localCenter + glm::vec3(localHalf.x,  localHalf.y, -localHalf.z),
        localCenter + glm::vec3(localHalf.x,  localHalf.y,  localHalf.z),
        localCenter + glm::vec3(-localHalf.x,  localHalf.y,  localHalf.z),
    };

    glm::vec3 wMin(99999.f), wMax(-99999.f);

    for (int i = 0; i < 8; i++)
    {
        glm::vec3 w = rotMat * corners[i] + pos;

        wMin = glm::min(wMin, w);
        wMax = glm::max(wMax, w);
    }

    m_worldMin = wMin;
    m_worldMax = wMax;
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
