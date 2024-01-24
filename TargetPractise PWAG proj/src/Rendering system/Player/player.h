#pragma once
#include "playerStats.h"
#include "../../State machine/gameAssets.h"
#include "../../Event system/keyboard.h"
#include "../../Event system/mouse.h"

class Player
{
public:
	Player();
	Player(glm::vec3 startPosition = glm::vec3(0.0f));
	~Player();

	void input(GameReference& gameReference, Keyboard& keyboard, float deltaTime);

	void update(float deltaTime);

	void setCameraUniforms(ShaderProgram* shaderProgram);
	void setCameraPosition(glm::vec3 _position);

	glm::vec3 getCameraPosition();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getDirection();
	glm::vec3 getUp();
	PlayerStats* getStats();
	Light::Point* getLight();

private:
	void _processInput(GameReference& gameReference, Keyboard& keyboard, float deltaTime);
	void _updateMatricesFromInput();

	void _updateLight();

	PlayerStats* _stats;
	Light::Point* _light;

	glm::vec3 _movementDirection = glm::vec3(0, 0, 0);
	glm::vec3 _position = glm::vec3(0, 0, 5);
	float _horizontalAngle = 3.14f;
	float _verticalAngle = 0.0f;
	float _initialFoV = 45.0f;

	float _speed = 3.0f;
	float _mouseSpeed = 0.005f;

	glm::vec3 _direction = glm::vec3(0.0f);
	glm::vec3 _right = glm::vec3(0.0f);
	glm::vec3 _up = glm::vec3(0.0f);

	glm::mat4 _viewMatrix = glm::mat4(0.0f);
	glm::mat4 _projectionMatrix = glm::mat4(0.0f);
};