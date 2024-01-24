#pragma once
#include "pch.h"
#include "entity.h"
#include <string>

Entity::Entity(GameObject* gameObj, std::string name)
{
	_gameObj = gameObj;
	setName(name);
}

Entity::~Entity()
{
	Debug::Log("Destroyed entity " + _name);
	delete _gameObj;
}

void Entity::update(float deltaTime)
{
}

void Entity::draw(ShaderProgram* shaderProgram)
{
	_gameObj->draw(shaderProgram);
}

void Entity::destroy()
{
	delete this;
}

void Entity::setName(std::string name)
{
	_name = name;
}

std::string Entity::getName()
{
	return _name;
}

void Entity::setPosition(const glm::vec3 _position)
{
	_gameObj->setPosition(_position);
}

glm::vec3 Entity::getPosition()
{
	return _gameObj->getPosition();
}

void Entity::setOrigin(const glm::vec3 origin)
{
	_gameObj->setOrigin(origin);
}

void Entity::setRotation(const glm::vec3 rotation)
{
	_gameObj->setRotation(rotation);
}

glm::vec3 Entity::getRotation()
{
	return _gameObj->getRotation();
}

void Entity::setScale(const glm::vec3 scale)
{
	_gameObj->setScale(scale);
}

void Entity::setDirection(glm::vec3 direction)
{
	_direction = direction;
}

glm::vec3 Entity::getDirection()
{
	return _direction;
}

void Entity::moveWithDirection(float deltaTime)
{
	glm::vec3 newPosition = getPosition() + (deltaTime * _speed * _direction);
	setPosition(newPosition);
}

void Entity::setSpeed(float speed)
{
	_speed = speed;
}

float Entity::getSpeed()
{
	return _speed;
}

void Entity::setColliderRadius(float colRad)
{
	_colRad = colRad;
}

float Entity::getColliderRadius()
{
	return _colRad;
}
