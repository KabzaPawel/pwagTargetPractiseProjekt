#pragma once
#include "dataOBJ.h"
#include "indexedDataOBJ.h"

class Mesh
{
public:
	Mesh();
	Mesh(DataOBJ objData, glm::vec3 _offset);
	Mesh(Mesh& src);
	virtual ~Mesh();

	void drawMesh();

	void setMeshUniform(ShaderProgram* shaderProgram);
	void setMatrixModel(glm::vec3 meshPosition, glm::vec3 meshOrigin, glm::vec3 meshRotation, glm::vec3 meshScale);

	glm::vec3 getOffset();
	DataOBJ getMeshData();
	IndexedDataOBJ getIndexedMeshData();

private:
	void _initBuffers();

	DataOBJ _meshData;
	IndexedDataOBJ _indexedData;

	glm::vec3 _offset;
	std::vector<glm::vec3> _offsets;
	glm::mat4 _matrixModel;

	GLuint _vertexArrayID;
	GLuint _elementBuffer;

	GLuint _verticesBuffer;
	GLuint _colorsBuffer;
	GLuint _normalsBuffer;
	GLuint _tangentBuffer;
	GLuint _bitangentBuffer;
	GLuint _uvsBuffer;
	GLuint _offsetBuffer;
};

