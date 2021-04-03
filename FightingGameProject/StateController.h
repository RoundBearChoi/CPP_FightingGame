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

		~StateController();
		void MakeStateTransition();

		template<class T>
		void CreateNewState()
		{
			State* s = State::NewState<T>();

			if (s != nullptr)
			{
				delete currentState;
				currentState = s;
			}
		}
	};
}