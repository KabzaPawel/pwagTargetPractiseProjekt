#include "pch.h"
#include "gameState.h"
#include "../Rendering system/Main level/MainLevel.h"

GameState::GameState(GameReference gameReference)
{
	_gameReference = gameReference;
}

GameState::~GameState() 
{
	delete _mainLevel;
}

void GameState::initialization()
{
	_mainLevel = new MainLevel(this);
	glfwSetInputMode(_gameReference->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_cursorDisabled = true;
}

void GameState::processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse)
{
	_mainLevel->input(deltaTime, _gameReference, keyboard, mouse);
}

void GameState::update(float deltaTime)
{
	_mainLevel->update(deltaTime);
}

void GameState::render(float deltaTime, bool wireframe)
{
	_mainLevel->draw(deltaTime, wireframe);
}

void GameState::winLevel(std::string time)
{
	std::string winText = "You won! Time: " + time + "s";
	Debug::LogSuccess(winText);
	_gameReference->_stateMachine.addNewState(StateReference(new GameOverState(_gameReference, winText)));
}
