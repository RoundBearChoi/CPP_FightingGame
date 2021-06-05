#pragma once
#include <vector>
#include "ObjGroup.h"
#include "Updater.h"
#include "InputBuffer.h"
#include "IGroupComponent.h"

namespace RB
{
	class FightersFixedUpdater : public Updater
	{
	private:
		ObjGroup* _fighters = nullptr;
		std::vector<IGroupComponent*> _vecComponents;

	public:
		FightersFixedUpdater(ObjGroup* fighters, IGroupComponent* fighterDirection, IGroupComponent* fighterJump, IGroupComponent* groundToGroundCol, IGroupComponent* specialMoveProc)
		{
			_fighters = fighters;
			_vecComponents.push_back(fighterDirection);
			_vecComponents.push_back(fighterJump);
			_vecComponents.push_back(groundToGroundCol);
			_vecComponents.push_back(specialMoveProc);
		}

		void CustomUpdate() override
		{
			InputBuffer::ptr->AddInputs();

			for (size_t i = 0; i < _vecComponents.size(); i++)
			{
				_vecComponents[i]->Update();
			}

			std::vector<GameObj*>& vecFighters = *_fighters->GetVecObjs();

			for (GameObj* obj : vecFighters)
			{
				obj->stateController->MakeStateTransition();

				if (obj->stateController->currentState != nullptr)
				{
					obj->stateController->currentState->RunUpdateProcess();
				}
			}

			UpdateUpdateCount();
		}
	};
}