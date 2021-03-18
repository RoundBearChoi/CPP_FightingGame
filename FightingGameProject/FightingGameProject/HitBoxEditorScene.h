#pragma once
#include "Scene.h"
#include "GameData.h"
#include "GameObj.h"

#include "Fighter_0_Idle.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_WalkForward.h"

namespace RB
{
	class HitBoxEditorScene : public Scene
	{
	private:
		GameObj fighter;

	public:
		HitBoxEditorScene()
		{
			IF_COUT{ std::cout << "constructing HitBoxEditorScene" << std::endl; }
		}

		~HitBoxEditorScene() override
		{
			IF_COUT{ std::cout << "destructing HitBoxEditorScene" << std::endl; }
		}

		void InitScene() override
		{
			fighter.stateController.CreateNewState<Fighter_0_Idle>();
			fighter.objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			fighter.objData.SetCreationID(1);
		}

		void Update(GameData& gameData) override
		{
			fighter.stateController.MakeStateTransition();
			
			State* s = fighter.stateController.currentState;
			
			if (s != nullptr)
			{
				if (s->IsNew())
				{
					s->OnEnter(fighter.objData, gameData);
				}
			
				s->UpdateState(fighter.objData, gameData);
			}
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 20 }, "HitBoxEditor", olc::WHITE);

			RenderCenterMark(cam);
		}

		void RenderStates(bool update) override
		{
			SheetRenderer::Render(ptrDecalLoader, &fighter, cam, false);
		}
	};
}