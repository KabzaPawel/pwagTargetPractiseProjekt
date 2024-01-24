#pragma once
#include "pch.h"

class PlayerStats
{
public:
	PlayerStats();
	~PlayerStats();

	bool checkSafeTime(float deltaTime);
	void updateGameTime(float deltaTime);
	float getGameTime();

	void shoot();
	void reloadBullet(float deltaTime);
	bool canIShoot();
	float getReloadMaxTime();
	float getReloadTime();

	int getPoints();
	void addPoint();

	float getPlayerRadius();

private:
	float _safeTimeAfterHit = 2.0f;
	float _timeAfterLastHit;
	float _gameTime = 0.0f;
	float _reloadMaxTime = 1.0f;
	float _reloadTime = 0.0f;
	bool _canShoot = true;

	int _points = 0;

	bool _alreadyShoot = false;
	float _playerRadius = 0.3f;
};
