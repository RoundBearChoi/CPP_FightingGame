#pragma once
#include "Scene.h"
#include "GameData.h"
#include "GameObj.h"
#include "UIElement.h"
#include "BoxCollider.h"

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
		std::array<BoxCollider, 1> testing;

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
			fighter.stateController.CreateNewState<Fighter_0_Jab>();
			fighter.objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			fighter.objData.SetCreationID(1);
			fighter.objData.SetTransitionPermission(false);

			playIcon.ptrDecal = ptrDecalLoader->GetDecal((int32_t)FighterSpriteType::editor_playframe);
			playIcon.width = 54;
			playIcon.height = 42;
			playIcon.topLeft = { GameSettings::window_width / 2 - playIcon.width / 2, 10 };

			testing[0] = BoxCollider({ 0, 0 }, 60, 80, 0.0f);
		}

		void Update(GameData& gameData) override
		{
			//dummy fighter
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
			
			//play icon
			if (playIcon.MouseHovering(mousePos))
			{
				playIcon.tint = olc::GREEN;

				if (gameData.mouse0 != nullptr)
				{
					gameData.mouse0->processed = true;
					fighter.stateController.currentState->animationController.UpdateTileIndex(true);
				}
			}
			else
			{
				playIcon.tint = olc::WHITE;
			}
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 15 }, "HitBox Editor", olc::WHITE);

			RenderCenterMark(cam);

			//current index # for animation
			olc::vi2d indexString = { playIcon.topLeft.x - 40, playIcon.topLeft.y + playIcon.height + 10 };
			AnimationStatus* status = fighter.stateController.currentState->animationController.GetStatus();
			olc::Renderer::ptrPGE->DrawString(indexString, "currentIndex: " + std::to_string(status->nCurrentTile), olc::WHITE);

			//boxcolliders
			std::array<olc::vi2d, 4> box0Pos;
			box0Pos[0] = RelativeVector::GetPosition(testing[0].TopLeft(), cam);
			box0Pos[1] = RelativeVector::GetPosition(testing[0].BottomLeft(), cam);
			box0Pos[2] = RelativeVector::GetPosition(testing[0].BottomRight(), cam);
			box0Pos[3] = RelativeVector::GetPosition(testing[0].TopRight(), cam);

			olc::Renderer::ptrPGE->DrawLine(box0Pos[0], box0Pos[1], olc::RED);
			olc::Renderer::ptrPGE->DrawLine(box0Pos[1], box0Pos[2], olc::RED);
			olc::Renderer::ptrPGE->DrawLine(box0Pos[2], box0Pos[3], olc::RED);
			olc::Renderer::ptrPGE->DrawLine(box0Pos[3], box0Pos[0], olc::RED);
		}

		void RenderStates(bool update) override
		{
			//dummy fighter
			SheetRenderer::Render(ptrDecalLoader, &fighter, cam);

			//play icon
			olc::Renderer::ptrPGE->DrawDecal(playIcon.topLeft, playIcon.ptrDecal, { 1.0f, 1.0f }, playIcon.tint);
		}
	};
}