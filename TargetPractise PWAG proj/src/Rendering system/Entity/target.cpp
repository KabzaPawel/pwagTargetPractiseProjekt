#pragma once
#include "pch.h"
#include "target.h"
#include <string>

Target::Target(GameObject* gameObj, std::string name, float worldRadius) : Entity(gameObj, name)
{
	setPosition(Mathf::spawnTargetCoords(worldRadius));

	float colliderSize = 0.3;
	float modelSize = 0.01;
	setScale(glm::vec3(modelSize, modelSize, modelSize));
	setColliderRadius(colliderSize);
}

Target::~Target()
{
}

void Target::update(float deltaTime)
{
	Entity::update(deltaTime);

	moveWithDirection(deltaTime);
}

void Target::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

void Target::destroy()
{
	delete this;
}

void Target::changeDirectionOnCollision()
{

}