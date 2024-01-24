#include "pch.h"
#include "mathf.h"

float Mathf::randVal(float min, float max)
{
	static std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

glm::vec3 Mathf::randCoordsInSphere(float radius)
{
	float x = randVal(-1, 1);
	float y = randVal(-1, 1);
	float z = randVal(-1, 1);

	float mag = glm::sqrt((x * x) + (y * y) + (z * z));
	float d = randVal(0, radius) / mag;

	x *= d;
	y *= d;
	z *= d;
	return glm::vec3(x, y, z);
}

glm::vec3 Mathf::spawnTargetCoords(float radius)
{
	float x = int(randVal(0, 20)) % 10;
	float y = 1;
	float z = int(randVal(0, 20)) % 10;

	float mag = 1;
	float d = 1;

	x *= d;
	y *= d;
	z *= d;
	return glm::vec3(x, y, z);
}

bool Mathf::areSpheresCollided(glm::vec3 center1, float rad1, glm::vec3 center2, float rad2)
{
	float radSum = rad1 + rad2;
	float distance = glm::distance(center1, center2);

	return (radSum > distance);
}

glm::vec3 Mathf::zeroVec()
{
	return glm::vec3(0);
}

glm::vec3 Mathf::oneVec()
{
	return glm::vec3(1);
}
