#include <vector>
#include <map>
#include <string.h>

#include <GLM/include/glm.hpp>
#include "pch.h"
#include "vboIndexer.h"

IndexedDataOBJ ObjectDataIndexer::indexVBO_TBN(DataOBJ& dataObj)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;
	IndexedDataOBJ indexedDataObj{};

	for (unsigned int i = 0; i < dataObj.vertices.size(); i++)
	{
		PackedVertex packed = { dataObj.vertices[i], dataObj.uvs[i], dataObj.normals[i] };

		unsigned short index;
		bool found = _getSimilarVertexIndexFast(packed, VertexToOutIndex, index);

		if (found)
		{
			indexedDataObj.indices.push_back(index);

			indexedDataObj.tangents[index] += dataObj.tangents[i];
			indexedDataObj.bittangents[index] += dataObj.bittangents[i];
		}
		else
		{
			indexedDataObj.vertices.push_back(dataObj.vertices[i]);
			indexedDataObj.uvs.push_back(dataObj.uvs[i]);
			indexedDataObj.normals.push_back(dataObj.normals[i]);
			indexedDataObj.tangents.push_back(dataObj.tangents[i]);
			indexedDataObj.bittangents.push_back(dataObj.bittangents[i]);

			unsigned short newindex = (unsigned short)indexedDataObj.vertices.size() - 1;
			indexedDataObj.indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}

	for (unsigned int i = 0; i < indexedDataObj.vertices.size(); i++)
	{
		indexedDataObj.colors.push_back(dataObj.colors[0]);
	}

	return indexedDataObj;
}

void ObjectDataIndexer::indexVBO(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

		unsigned short index;
		bool found = _getSimilarVertexIndexFast(packed, VertexToOutIndex, index);

		if (found)
		{
			out_indices.push_back(index);
		}
		else
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

void ObjectDataIndexer::indexVBO_TBN(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,
	std::vector<glm::vec3>& in_tangents,
	std::vector<glm::vec3>& in_bitangents,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals,
	std::vector<glm::vec3>& out_tangents,
	std::vector<glm::vec3>& out_bitangents
)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

		unsigned short index;
		bool found = _getSimilarVertexIndexFast(packed, VertexToOutIndex, index);

		if (found)
		{
			out_indices.push_back(index);

			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}
		else
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_tangents.push_back(in_tangents[i]);
			out_bitangents.push_back(in_bitangents[i]);

			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

void ObjectDataIndexer::indexVBO_slow(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
)
{

	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		unsigned short index;
		bool found = _getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		if (found)
		{
			out_indices.push_back(index);
		}
		else
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}

bool ObjectDataIndexer::_isNear(float v1, float v2)
{
	return fabs(v1 - v2) < 0.01f;
}

bool ObjectDataIndexer::_getSimilarVertexIndex(
	glm::vec3& in_vertex,
	glm::vec2& in_uv,
	glm::vec3& in_normal,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals,
	unsigned short& result
) 
{
	for (unsigned int i = 0; i < out_vertices.size(); i++) {
		if (
			_isNear(in_vertex.x, out_vertices[i].x) &&
			_isNear(in_vertex.y, out_vertices[i].y) &&
			_isNear(in_vertex.z, out_vertices[i].z) &&
			_isNear(in_uv.x, out_uvs[i].x) &&
			_isNear(in_uv.y, out_uvs[i].y) &&
			_isNear(in_normal.x, out_normals[i].x) &&
			_isNear(in_normal.y, out_normals[i].y) &&
			_isNear(in_normal.z, out_normals[i].z)
			) {
			result = i;
			return true;
		}
	}
	return false;
}

bool ObjectDataIndexer::_getSimilarVertexIndexFast(
	PackedVertex& packed,
	std::map<PackedVertex, unsigned short>& VertexToOutIndex,
	unsigned short& result
)
{
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end())
	{
		return false;
	}
	else
	{
		result = it->second;
		return true;
	}
}