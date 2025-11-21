#pragma once
#include "GameObject.h"

class Fance : public GameObject
{
public:
	Fance(const glm::vec3& position);
};

class House : public GameObject
{
public:
	House(const glm::vec3& position);
};

class Ground : public GameObject
{
public:
	Ground(const glm::vec3& position);
};

class Tree : public GameObject
{
public:
	Tree(const glm::vec3& position);
};

class Boat : public GameObject
{
public:
	Boat(const glm::vec3& position);
};