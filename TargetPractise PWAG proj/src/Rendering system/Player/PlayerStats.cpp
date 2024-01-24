#include "pch.h"
#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	_timeAfterLastHit = _safeTimeAfterHit;
}

PlayerStats::~PlayerStats()
{

}

bool PlayerStats::checkSafeTime(float deltaTime)
{
	if (_safeTimeAfterHit <= _timeAfterLastHit)
	{
		return true;
	}
	else
	{
		_timeAfterLastHit += deltaTime;
		return false;
	}
}

float PlayerStats::getGameTime()
{
	return _gameTime;
}

void PlayerStats::updateGameTime(float deltaTime)
{
	_gameTime += deltaTime;
}

void PlayerStats::shoot()
{
	if (_canShoot)
	{
		_canShoot = false;
		_reloadTime = 0.0f;
	}
}

void PlayerStats::reloadBullet(float deltaTime)
{
	if (!_canShoot)
	{
		if (_reloadTime < _reloadMaxTime)
		{
			_reloadTime += deltaTime;
		}
		else
		{
			_canShoot = true;
		}
	}
}

bool PlayerStats::canIShoot()
{
	return _canShoot;
}

float PlayerStats::getReloadMaxTime()
{
	return _reloadMaxTime;
}

float PlayerStats::getReloadTime()
{
	return _reloadTime;
}

int PlayerStats::getPoints()
{
	return _points;
}

void PlayerStats::addPoint()
{
	_points++;
}

float PlayerStats::getPlayerRadius()
{
	return _playerRadius;
}
