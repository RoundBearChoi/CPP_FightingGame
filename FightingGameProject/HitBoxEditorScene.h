#pragma once
#include "Scene.h"
#include "GameData.h"
#include "GameObj.h"
#include "UIElement.h"

#include "Fighter_0_Idle.h"
#include "Fighter_0_Jab.h"
#include "Fighter_0_WalkForward.h"

namespace RB
{
	class HitBoxEditorScene : public Scene
	{
	private:
		GameObj fighter;
		UIElement playIcon;

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

			playIcon.ptrDecal = ptrDecalLoader->GetDecal((int32_t)FighterSpriteType::editor_playframe);
			playIcon.topLeft = { GameSettings::window_width / 2 - 54 / 2, 10 };
			playIcon.width = 54;
			playIcon.height = 42;
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



			olc::vi2d mousePos = olc::Platform::ptrPGE->GetMousePos();
			
			if (playIcon.MouseHovering(mousePos))
			{
				if (gameData.mouse0 != nullptr)
				{
					gameData.mouse0->processed = true;
					fighter.stateController.currentState->animationController.UpdateTileIndex(true);
				}
			}
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 15 }, "HitBox Editor", olc::WHITE);

			RenderCenterMark(cam);
		}

		void RenderStates(bool update) override
		{
			SheetRenderer::Render(ptrDecalLoader, &fighter, cam);

			olc::Renderer::ptrPGE->DrawDecal(playIcon.topLeft, playIcon.ptrDecal);
		}
	};
}