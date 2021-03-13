#pragma once
#include "State.h"

namespace RB
{
	class StateController
	{
	private:
		size_t creationID = 0;
		State* prevState = nullptr;

	public:
		State* currentState = nullptr;

		~StateController();
		void MakeStateTransition();
		void SetCreationID(size_t _id);

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