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
			if (_stopCount > 0)
			{
				_stopCount--;
			}
			else
			{
				DoUpdate();
			}
		}

		void DoUpdate()
		{
			InputBuffer::ptr->AddInputs();
			std::vector<GameObj*>& vecFighters = *_fighters->GetVecObjs();

			for (size_t i = 0; i < vecFighters.size(); i++)
			{
				vecFighters[i]->objData.SetPreviousPosition(vecFighters[i]->objData.GetPosition());
			}

			for (size_t i = 0; i < (*_vecUpdateComponents).size(); i++)
			{
				(*_vecUpdateComponents)[i]->Update();
			}

			for (size_t i = 0; i < vecFighters.size(); i++)
			{
				vecFighters[i]->stateController->MakeStateTransition();

				if (vecFighters[i]->stateController->currentState != nullptr)
				{
					vecFighters[i]->stateController->currentState->RunUpdateProcess();
				}
			}

			_fighters->UpdateSpriteTileIndex();

			ProcessStopCounts();
			UpdateUpdateCount();
		}
	};
}