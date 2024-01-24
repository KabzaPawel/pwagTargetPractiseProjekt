#pragma once
#include "entity.h"
#include "../Rendering system/Model/gameObject.h"

class LivingEntity : public Entity
{
public:
	LivingEntity(GameObject* gameObj, std::string name, float lifeSpan);
	~LivingEntity();

	void update(float deltaTime);

	void draw(ShaderProgram* shaderProgram);

	void destroy();

	bool isDead();

protected:
	float _lifeSpan = 0;
	float _age = 0.0f;
	bool _dead = false;

private:
	void _calcAge(float deltaTime);
};