#pragma once
#include <vector>

struct DataOBJ
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;

	std::vector <glm::vec3> tangents;
	std::vector <glm::vec3> bittangents;
	std::vector <glm::vec2> uvs;
};