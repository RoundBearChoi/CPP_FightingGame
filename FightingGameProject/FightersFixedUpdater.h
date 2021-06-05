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
		std::vector<IGroupComponent*> _vecUpdateComponents;
		std::vector<IGroupComponent*> _vecStateRenderComponents;

	public:
		FightersFixedUpdater(ObjGroup* fighters, IGroupComponent* fighterDirection, IGroupComponent* fighterJump, IGroupComponent* groundToGroundCol, IGroupComponent* specialMoveProc, IGroupComponent* animationRenderer)
		{
			_fighters = fighters;
			_vecUpdateComponents.push_back(fighterDirection);
			_vecUpdateComponents.push_back(fighterJump);
			_vecUpdateComponents.push_back(groundToGroundCol);
			_vecUpdateComponents.push_back(specialMoveProc);

			_vecStateRenderComponents.push_back(animationRenderer);
		}

		void CustomUpdate() override
		{
			InputBuffer::ptr->AddInputs();

			for (size_t i = 0; i < _vecUpdateComponents.size(); i++)
			{
				_vecUpdateComponents[i]->Update();
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
			for (size_t i = 0; i < _vecStateRenderComponents.size(); i++)
			{
				_vecStateRenderComponents[i]->Update();
			}
		}
	};
}