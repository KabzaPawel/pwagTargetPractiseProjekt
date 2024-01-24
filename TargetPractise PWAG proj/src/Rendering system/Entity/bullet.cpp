#pragma once
#include "pch.h"
#include "livingEntity.h"
#include "bullet.h"
#include <string>

Bullet::Bullet(GameObject* gameObj, std::string name, float lifeSpan, Player* player) : LivingEntity(gameObj, name, lifeSpan)
{
	setPosition(player->getCameraPosition() + player->getDirection() * 0.3f);
	setOrigin(player->getCameraPosition());

	setScale(Mathf::oneVec() * 0.05f);
	setColliderRadius(0.5f);

	setDirection(player->getDirection());
	setSpeed(60);

	_light = new Light::Point(getPosition(), { 0,1,0 });
}

Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime)
{
	LivingEntity::update(deltaTime);

	moveWithDirection(deltaTime);
	_light->setPosition(getPosition());
}

void Bullet::draw(ShaderProgram* shaderProgram)
{
	LivingEntity::draw(shaderProgram);
}

void Bullet::destroy()
{
	delete this;
}

Light::Point* Bullet::getLight()
{
	return _light;
}
