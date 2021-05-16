#pragma once
#include <array>
#include "GroupComponent.h"
#include "Hadouken.h"
#include "BufferChecker.h"
#include "InputBuffer.h"

namespace RB
{
	class Fighter_0_Hadouken_Fire;

	class SpecialMoveProcessor : public GroupComponent
	{
	public:
		void Update(GameObj& obj) override
		{
			Hadouken hadouken;
			std::vector<InputElement>* vecInputs = nullptr;

			if (obj.objData.GetCreationID() == 1)
			{
				vecInputs = &InputBuffer::ptr->vecP1Inputs;
			}
			else
			{
				vecInputs = &InputBuffer::ptr->vecP2Inputs;
			}

			if (vecInputs != nullptr)
			{
				if (BufferChecker::Correct(hadouken, *vecInputs, obj))
				{
					obj.stateController->currentState->nextState = State::NewState<Fighter_0_Hadouken_Fire>(&obj.objData);
				}
			}
		}
	};
}