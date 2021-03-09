#pragma once
#include "State.h"

namespace RB
{
	class StateController
	{
	private:
		size_t creationID = 0;

	public:
		State* currentState = nullptr;

		~StateController()
		{
			IF_COUT{ std::cout << "destructing StateController: " << creationID << std::endl; }

			delete currentState;
		}

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

		void SetCreationID(size_t _id)
		{
			creationID = _id;
		}
	};
}