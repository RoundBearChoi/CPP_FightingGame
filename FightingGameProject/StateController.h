#pragma once
#include "State.h"
#include "DevSettings.h"
#include "StateFactory.h"

namespace RB
{
	class StateController
	{
	private:
		State* prevState = nullptr;
		StateFactory* _stateFactory = nullptr;

	public:
		State* currentState = nullptr;

		StateController(StateFactory* stateFactory);
		~StateController();
		void MakeStateTransition();
	};
}