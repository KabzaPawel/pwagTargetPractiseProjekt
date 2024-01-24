#pragma once
#include "programState.h"
#include "stateMachine.h"
#include "gameAssets.h"
#include "menuState.h"

class GameOverState : public ProgramState
{
public:
	GameOverState(GameReference gameReference, std::string header);
	~GameOverState();

	void initialization() override;
	void processInput(float deltaTime, Keyboard& keyboard, Mouse& mouse) override;
	void update(float deltaTime) override;
	void render(float deltaTime, bool wireframe) override;

private:
	GameReference _gameReference;

	Button _winLabel;
	Button _menuButton;

	Sprite _starsBackground;
	Sprite _logo;
	Sprite _iconLogo;
};
