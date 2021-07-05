#pragma once
#include <array>
#include "IGroupComponent.h"
#include "Hadouken.h"
#include "BufferChecker.h"
#include "InputBuffer.h"

namespace RB
{
	class Fighter_0_Hadouken_Fire;

	class SpecialMoveProcessor : public IGroupComponent
	{
	private:
		std::vector<ObjBase*>* _vecFighters = nullptr;

	public:
		SpecialMoveProcessor(std::vector<ObjBase*>* vecFighters)
		{
			_vecFighters = vecFighters;
		}

		void Update() override
		{
			std::vector<ObjBase*>& vec = *_vecFighters;

			for (size_t i = 0; i < vec.size(); i++)
			{
				TriggerSpecialMove(*vec[i]);
			}
		}

		void TriggerSpecialMove(ObjBase& obj)
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
					obj.GetCurrentState()->nextState = State::NewState<Fighter_0_Hadouken_Fire>(&obj);
				}
			}
		}
	};
}