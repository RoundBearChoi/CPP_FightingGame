#pragma once
#include "State.h"

namespace RB
{
	class StateController
	{
	public:
		State* currentState = nullptr;

		~StateController()
		{
			IF_COUT{ std::cout << "destructing StateController" << std::endl; }

			delete currentState;
		}

		template<class T>
		void CreateNewState()
		{
			State* newState = State::CreateState<T>();

			if (newState != nullptr)
			{
				delete currentState;
				currentState = newState;
			}
		}

		void MakeStateTransition()
		{
			State* next = currentState->nextState;

			if (next != nullptr)
			{
				delete currentState;
				currentState = next;
				currentState->nextState = nullptr;
			}
		}
	};
}