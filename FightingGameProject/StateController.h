#pragma once
#include "State.h"
#include "DevSettings.h"

namespace RB
{
	class StateController
	{
	private:
		State* prevState = nullptr;

	public:
		State* currentState = nullptr;

		StateController();
		~StateController();

		void MakeStateTransition();
	};
}