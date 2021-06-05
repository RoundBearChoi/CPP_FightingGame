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
		std::vector<IGroupComponent*>* _vecUpdateComponents;

	public:
		FightersFixedUpdater(ObjGroup* fighters, std::vector<IGroupComponent*>* updateComponents)
		{
			_fighters = fighters;

			_vecUpdateComponents = updateComponents;
		}

		void CustomUpdate() override
		{
			InputBuffer::ptr->AddInputs();

			for (size_t i = 0; i < (*_vecUpdateComponents).size(); i++)
			{
				(*_vecUpdateComponents)[i]->Update();
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

			_fighters->UpdateSpriteTileIndex();

			UpdateUpdateCount();
		}
	};
}