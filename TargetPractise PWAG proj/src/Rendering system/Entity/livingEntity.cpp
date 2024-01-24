#pragma once
#include "pch.h"
#include "entity.h"
#include "livingEntity.h"
#include <string>

LivingEntity::LivingEntity(GameObject* gameObj, std::string name, float lifeSpan) : Entity(gameObj, name)
{
	_lifeSpan = lifeSpan;
}

LivingEntity::~LivingEntity()
{
}

void LivingEntity::update(float deltaTime)
{
	Entity::update(deltaTime);

	_calcAge(deltaTime);
	if (isDead())
	{
		Debug::Log("Object " + _name + " Expired");
	}
}

void LivingEntity::draw(ShaderProgram* shaderProgram)
{
	Entity::draw(shaderProgram);
}

void LivingEntity::destroy()
{
	delete this;
}

bool LivingEntity::isDead()
{
	return _dead;
}

void LivingEntity::_calcAge(float deltaTime)
{
	_age += deltaTime;
	_dead = _age > _lifeSpan;
}