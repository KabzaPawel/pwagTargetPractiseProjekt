#pragma once
#include "livingEntity.h"
#include "../Lighting/point.h"

class Bullet : public LivingEntity
{
public:
	Bullet(GameObject* gameObj, std::string name, float lifeSpan, Player* player);
	~Bullet();

	void update(float deltaTime);

	void draw(ShaderProgram* shaderProgram);

	void destroy();

	Light::Point* getLight();

private:
	Light::Point* _light;
};