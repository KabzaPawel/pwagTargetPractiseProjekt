#pragma once
#include <random>
#include "GLM/include/glm.hpp"

class Mathf
{
public:
	Mathf() = delete;

	static float randVal(float min, float max);
	static glm::vec3 randCoordsInSphere(float radius);
	static glm::vec3 spawnTargetCoords(float radius);

	static bool areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2);

	static glm::vec3 zeroVec();
	static glm::vec3 oneVec();
};