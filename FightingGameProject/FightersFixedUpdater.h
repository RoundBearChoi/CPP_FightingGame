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
		std::vector<IGroupComponent*>* _vecStateRenderComponents;

	public:
		FightersFixedUpdater(ObjGroup* fighters, std::vector<IGroupComponent*>* updateComponents, std::vector<IGroupComponent*>* renderComponents)
		{
			_fighters = fighters;

			_vecUpdateComponents = updateComponents;
			_vecStateRenderComponents = renderComponents;
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

			UpdateUpdateCount();
		}

		void CustomRender() override
		{
			for (size_t i = 0; i < (*_vecStateRenderComponents).size(); i++)
			{
				(*_vecStateRenderComponents)[i]->Update();
			}
		}
	};
}