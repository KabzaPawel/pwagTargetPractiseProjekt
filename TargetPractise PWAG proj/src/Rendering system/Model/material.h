#pragma once

class Material
{
public:
	Material();
	Material(Texture* _mainTexture, Texture* specular, Texture* _normalMap, int _diffuseLerp, int _normalLerp, glm::vec3 _ambientLight);
	Material(Material& src);
	virtual ~Material();

	void setTextures(Texture* texture, Texture* specular, Texture* _normalMap);
	void setUniformValues(int _diffuseLerp, int _normalLerp, glm::vec3 _ambientLight);

	int GetDiffuseLerp();
	int GetNormalLerp();
	glm::vec3 GetAmpientLight();

	Texture* GetMainTexture();
	Texture* GetSpecularTexture();
	Texture* GetNormalMap();

	void bindTextures();
	void setMaterialShaderUniforms(ShaderProgram& shaderProgram);

private:
	int _diffuseLerp;
	int _normalLerp;
	glm::vec3 _ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);

	Texture* _mainTexture;
	Texture* _specularTexture;
	Texture* _normalMap;
};