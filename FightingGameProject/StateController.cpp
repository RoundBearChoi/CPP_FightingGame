#include "StateController.h"
#include "DevSettings.h"

namespace RB
{
	StateController::~StateController()
	{
		IF_COUT{ std::cout << "destructing StateController: " << creationID << std::endl; };
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

	void StateController::SetCreationID(size_t _id)
	{
		creationID = _id;
	}
}