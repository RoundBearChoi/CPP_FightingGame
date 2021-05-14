#include "StateController.h"

namespace RB
{
	StateController::StateController(/*StateFactory* stateFactory*/)
	{
		//_stateFactory = stateFactory;
	}

	StateController::~StateController()
	{
		IF_COUT{ std::cout << "destructing StateController" << std::endl; };
		delete currentState;
	}

	void StateController::MakeStateTransition()
	{
		State* next = currentState->nextState;

		if (next != nullptr)
		{
			delete currentState;
			currentState = next;
			currentState->nextState = nullptr;
		}
	}
}