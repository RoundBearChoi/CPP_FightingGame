#pragma once
#include <array>
#include "GameObj.h"
#include "Hadouken.h"
#include "BufferChecker.h"
#include "InputBuffer.h"

namespace RB
{
	class Fighter_0_Hadouken_Fire;

	class SpecialMoveProcessor
	{
	public:
		void Update(std::array<GameObj, 2>& arrObjs)
		{
			Hadouken h1;
			Hadouken h2;
			h1.SetCombo();
			h2.SetCombo();

			if (BufferChecker::Correct(h1, InputBuffer::ptr->vecP1Inputs, arrObjs[0]))
			{
				arrObjs[0].stateController.currentState->nextState = State::NewState<Fighter_0_Hadouken_Fire>();
			}

			if (BufferChecker::Correct(h2, InputBuffer::ptr->vecP2Inputs, arrObjs[1]))
			{
				arrObjs[1].stateController.currentState->nextState = State::NewState<Fighter_0_Hadouken_Fire>();
			}
		}
	};
}