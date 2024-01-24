#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "menuState.h"
#include "gameState.h"

class MenuState : public ProgramState
{
public:
	MenuState(GameReference gameReference);
	~MenuState();

	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;

private:
	GameReference _gameReference;
	Player _camera;

	Button _newGameButton;
	Button _exitGameButton;

	Sprite _background;
	Sprite _logo;
};
