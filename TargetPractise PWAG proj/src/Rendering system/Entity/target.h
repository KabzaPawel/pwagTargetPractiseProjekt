#pragma once
#include "entity.h"
#include "../Lighting/point.h"
#include "../Shader/shaderProgram.h"
#include <string>

class Target : public Entity
{
public:
	Target(GameObject* gameObj, std::string name, float worldRadius);
	~Target();

	void update(float deltaTime);

	void draw(ShaderProgram* shaderProgram);

	void destroy();

	void changeDirectionOnCollision();
};