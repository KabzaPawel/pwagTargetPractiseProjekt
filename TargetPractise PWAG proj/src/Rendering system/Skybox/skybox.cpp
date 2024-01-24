#include "pch.h"
#include "skybox.h"

float skyboxVertices[] =
{
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	1, 2, 6,
	6, 5, 1,
	0, 4, 7,
	7, 3, 0,
	4, 5, 6,
	6, 7, 4,
	0, 3, 2,
	2, 1, 0,
	0, 1, 5,
	5, 4, 0,
	3, 7, 6,
	6, 2, 3
};

Skybox::Skybox(std::string facesCubemap[6])
{
	InitializeShader();
	InitializeBuffers();
	InitializeTextures(facesCubemap);
}

Skybox::~Skybox()
{
	delete this->_shaderProgram;
	glDeleteBuffers(1, &_skyboxVBO);
	glDeleteBuffers(1, &_skyboxEBO);
	glDeleteTextures(1, &_cubemapTexture);
	glDeleteVertexArrays(1, &_skyboxVAO);
}

void Skybox::InitializeShader()
{
	_fragShader = Shader::createShaderFromFile("shaders/skybox.frag", Shader::Type::eFragment);
	_vertShader = Shader::createShaderFromFile("shaders/skybox.vert", Shader::Type::eVertex);

	_shaderProgram = new ShaderProgram();
	_shaderProgram->attachShader(_fragShader);
	_shaderProgram->attachShader(_vertShader);
	_shaderProgram->linkShaderProgram();

	_shaderProgram->useShader();
	_shaderProgram->setInt("skybox", 0);
}

void Skybox::InitializeBuffers()
{
	glGenVertexArrays(1, &_skyboxVAO);
	glGenBuffers(1, &_skyboxVBO);
	glGenBuffers(1, &_skyboxEBO);

	glBindVertexArray(_skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::InitializeTextures(std::string facesCubemap[6])
{
	glGenTextures(1, &_cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			Debug::LogError("Failed to load texture: " + facesCubemap[i]);
			stbi_image_free(data);
		}
	}
}


void Skybox::draw(glm::vec3 _position, glm::vec3 orientation, glm::vec3 up)
{
	glDepthFunc(GL_LEQUAL);

	_shaderProgram->useShader();
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::mat4(glm::mat3(glm::lookAt(_position, _position + orientation, up)));
	projection = glm::perspective(glm::radians(45.0f), (float)Config::g_defaultWidth / (float)Config::g_defaultHeight, 0.1f, 100.0f);

	_shaderProgram->setMat4("view", view);
	_shaderProgram->setMat4("projection", projection);

	glBindVertexArray(_skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}
