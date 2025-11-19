#include "PCH.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider(const glm::vec3& min, const glm::vec3& max)
    : localMin(min), localMax(max)
{
    worldMin = min;
    worldMax = max;
}

void BoxCollider::UpdateTransform(const glm::vec3& pos, const glm::vec3& scale, const glm::vec3& rot)
{
    glm::vec3 half = (localMax - localMin) * 0.5f * scale;
    glm::vec3 center = (localMax + localMin) * 0.5f;

    glm::vec3 worldCenter = center * scale + pos;

    worldMin = worldCenter - half;
    worldMax = worldCenter + half;
}

bool BoxCollider::IntersectSegment(const glm::vec3& start, const glm::vec3& end, glm::vec3& hitPoint, float* outT) const
{
    float t;
    if (!IntersectSegmentAABB(start, end, worldMin, worldMax, t, hitPoint))
        return false;

    if (outT) *outT = t;
    return true;
}

void BoxCollider::DrawDebug()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);

    // 하단 4개
    glVertex3f(worldMin.x, worldMin.y, worldMin.z);
    glVertex3f(worldMax.x, worldMin.y, worldMin.z);
    glVertex3f(worldMax.x, worldMin.y, worldMax.z);
    glVertex3f(worldMin.x, worldMin.y, worldMax.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // 상단 4개
    glVertex3f(worldMin.x, worldMax.y, worldMin.z);
    glVertex3f(worldMax.x, worldMax.y, worldMin.z);
    glVertex3f(worldMax.x, worldMax.y, worldMax.z);
    glVertex3f(worldMin.x, worldMax.y, worldMax.z);
    glEnd();

    // vertical lines
    glBegin(GL_LINES);
    glVertex3f(worldMin.x, worldMin.y, worldMin.z);
    glVertex3f(worldMin.x, worldMax.y, worldMin.z);

    glVertex3f(worldMax.x, worldMin.y, worldMin.z);
    glVertex3f(worldMax.x, worldMax.y, worldMin.z);

    glVertex3f(worldMax.x, worldMin.y, worldMax.z);
    glVertex3f(worldMax.x, worldMax.y, worldMax.z);

    glVertex3f(worldMin.x, worldMin.y, worldMax.z);
    glVertex3f(worldMin.x, worldMax.y, worldMax.z);
    glEnd();
}
