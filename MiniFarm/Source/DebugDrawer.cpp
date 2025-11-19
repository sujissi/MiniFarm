#include "PCH.h"
#include "DebugDrawer.h"
#include "Shader.h"

void DebugDrawer::DrawLine(const glm::vec3& a, const glm::vec3& b, const glm::vec3& color)
{
	Shader::BeginDebugDraw(color);

	glBegin(GL_LINES);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glEnd();

	Shader::EndDebugDraw();
}

void DebugDrawer::DrawArrow(const glm::vec3& pos, const glm::vec3& dir,
	float length, const glm::vec3& color)
{
	glm::vec3 nDir = glm::normalize(dir);
	glm::vec3 end = pos + nDir * length;

	Shader::BeginDebugDraw(color);

	glBegin(GL_LINES);
	glVertex3f(pos.x, pos.y, pos.z);
	glVertex3f(end.x, end.y, end.z);
	glEnd();

	glm::vec3 side = glm::normalize(glm::cross(nDir, glm::vec3(0, 1, 0)));
	glm::vec3 up = glm::normalize(glm::cross(side, nDir));

	float head = length * 0.2f;

	glm::vec3 left = end - nDir * head + side * (head * 0.6f);
	glm::vec3 right = end - nDir * head - side * (head * 0.6f);
	glm::vec3 top = end - nDir * head + up * (head * 0.6f);

	glBegin(GL_LINES);
	glVertex3f(end.x, end.y, end.z); glVertex3f(left.x, left.y, left.z);
	glVertex3f(end.x, end.y, end.z); glVertex3f(right.x, right.y, right.z);
	glEnd();

	Shader::EndDebugDraw();
}

void DebugDrawer::DrawAxis(const glm::vec3& pos, float size)
{
	DrawArrow(pos, { 1,0,0 }, size, { 1,0,0 }); // X 빨강
	DrawArrow(pos, { 0,1,0 }, size, { 0,1,0 }); // Y 초록
	DrawArrow(pos, { 0,0,1 }, size, { 0,0,1 }); // Z 파랑
}

void DebugDrawer::DrawBox(const glm::vec3& min, const glm::vec3& max, const glm::vec3& color)
{
	Shader::BeginDebugDraw(color);

	// ----- 아래 4개 -----
	glBegin(GL_LINE_LOOP);
	glVertex3f(min.x, min.y, min.z);
	glVertex3f(max.x, min.y, min.z);
	glVertex3f(max.x, min.y, max.z);
	glVertex3f(min.x, min.y, max.z);
	glEnd();

	// ----- 위 4개 -----
	glBegin(GL_LINE_LOOP);
	glVertex3f(min.x, max.y, min.z);
	glVertex3f(max.x, max.y, min.z);
	glVertex3f(max.x, max.y, max.z);
	glVertex3f(min.x, max.y, max.z);
	glEnd();

	// ----- 수직 4개 -----
	glBegin(GL_LINES);
	glVertex3f(min.x, min.y, min.z); glVertex3f(min.x, max.y, min.z);
	glVertex3f(max.x, min.y, min.z); glVertex3f(max.x, max.y, min.z);
	glVertex3f(max.x, min.y, max.z); glVertex3f(max.x, max.y, max.z);
	glVertex3f(min.x, min.y, max.z); glVertex3f(min.x, max.y, max.z);
	glEnd();

	Shader::EndDebugDraw();
}
