#pragma once
#include "../Rendering system/Model/gameObject.h"

class Entity 
{
public:
	Entity(GameObject* gameObj, std::string name);
	~Entity();

	void update(float deltaTime);

	void draw(ShaderProgram* shaderProgram);

	void destroy();

	void setName(std::string name);
	std::string getName();

	void setPosition(const glm::vec3 _position);
	glm::vec3 getPosition();
	void setOrigin(const glm::vec3 origin);

	void setRotation(const glm::vec3 rotation);
	glm::vec3 getRotation();

	void setScale(const glm::vec3 scale);

	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
	void moveWithDirection(float deltaTime);

	void setSpeed(float speed);
	float getSpeed();

	void setColliderRadius(float colRad);
	float getColliderRadius();

protected:
	GameObject* _gameObj = nullptr;

	std::string _name = "";
	glm::vec3 _direction = glm::vec3(0.0f);
	float _speed = 0;
	float _colRad = 0;
};