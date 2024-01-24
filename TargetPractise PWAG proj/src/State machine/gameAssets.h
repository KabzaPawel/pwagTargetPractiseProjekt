#pragma once
#include "stateMachine.h"

struct GameAssets
{
	GLFWwindow* window;
	StateMachine _stateMachine;
};

typedef	std::shared_ptr<GameAssets> GameReference;