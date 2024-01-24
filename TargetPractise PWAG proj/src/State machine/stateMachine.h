#pragma once
#include "programState.h"

typedef std::unique_ptr<ProgramState> StateReference;

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() = default;

	void addNewState(StateReference newState);
	void changingState();
	void deleteState();
	void removeAllStates();

	StateReference& getCurrentState();
	int getNrOfStates() const;

private:
	std::stack<std::unique_ptr<ProgramState>> _states;
	std::unique_ptr<ProgramState> _newState;

	int _nrStates = 0;
	bool _isAdded = false;
	bool _isRemoved = false;
};