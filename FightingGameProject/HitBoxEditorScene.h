#pragma once
#include "Scene.h"
#include "GameData.h"
#include "GameObj.h"
#include "UIElement.h"
#include "BoxCollider.h"
#include "TargetBodyType.h"

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
		std::array<BoxCollider, 2> arrBoxCol;
		TargetBodyType targetBodyType;

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

			arrBoxCol[0] = BoxCollider({ 0, 0 }, 40, 50, 0.0f);
			arrBoxCol[1] = BoxCollider({ 0, -100 }, 60, 70, 0.0f);
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

				if (gameData.key_mouse0)
				{
					gameData.key_mouse0->processed = true;
					fighter.stateController.currentState->animationController.UpdateTileIndex(true);
				}
			}
			else
			{
				playIcon.tint = olc::WHITE;
			}

			//boxcolliders
			if (gameData.key_t && gameData.key_y || !gameData.key_t && !gameData.key_y)
			{
				//double press (do nothing)
			}
			else if (gameData.key_t)
			{
				arrBoxCol[0].RotateCounterClockwise();
			}
			else if (gameData.key_y)
			{
				arrBoxCol[0].RotateClockwise();
			}
			
			if (gameData.key_g && gameData.key_h || !gameData.key_g && !gameData.key_h)
			{
				//double press (do nothing)
			}
			else if (gameData.key_g)
			{
				arrBoxCol[0].IncreaseWidth(1);
			}
			else if (gameData.key_h)
			{
				arrBoxCol[0].IncreaseHeight(1);
			}

			//resize, rotate, move boxcollider
			arrBoxCol[0].SetQuad();
			arrBoxCol[0].UpdateRotation();
			arrBoxCol[0].UpdatePosition( //up down left right
				gameData.key_a,
				gameData.key_d,
				gameData.key_w,
				gameData.key_s);

			arrBoxCol[1].SetQuad();
			arrBoxCol[1].UpdateRotation();
			arrBoxCol[1].UpdatePosition( //up down left right
				false,
				false,
				false,
				false);
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 15 }, "HitBox Editor", olc::WHITE);

			RenderCenterMark(cam);

			//boxcolliders
			for (int32_t i = 0; i < arrBoxCol.size(); i++)
			{
				std::array<olc::vi2d, 4> quad;
				quad[0] = RelativeVector::GetPosition(arrBoxCol[i].Point0(), cam);
				quad[1] = RelativeVector::GetPosition(arrBoxCol[i].Point1(), cam);
				quad[2] = RelativeVector::GetPosition(arrBoxCol[i].Point2(), cam);
				quad[3] = RelativeVector::GetPosition(arrBoxCol[i].Point3(), cam);

				olc::Pixel color = olc::BLUE;

				if (i == 1)
				{
					color = olc::RED;
				}

				olc::Renderer::ptrPGE->DrawLine(quad[0], quad[1], color);
				olc::Renderer::ptrPGE->DrawLine(quad[1], quad[2], color);
				olc::Renderer::ptrPGE->DrawLine(quad[2], quad[3], color);
				olc::Renderer::ptrPGE->DrawLine(quad[3], quad[0], color);
			}

			//current boxcollider info
			olc::Renderer::ptrPGE->DrawString({ 0, 200 }, "position: ", olc::WHITE);
			olc::Renderer::ptrPGE->DrawString({ 0, 200 + 12 }, "width: ", olc::WHITE);
			olc::Renderer::ptrPGE->DrawString({ 0, 200 + 24 }, "height: ", olc::WHITE);
			olc::Renderer::ptrPGE->DrawString({ 0, 200 + 36 }, "rotation: ", olc::WHITE);

			//current index # for animation
			olc::vi2d indexString = { playIcon.topLeft.x - 40, playIcon.topLeft.y + playIcon.height + 10 };
			AnimationStatus* status = fighter.stateController.currentState->animationController.GetStatus();
			olc::Renderer::ptrPGE->DrawString(indexString, "currentIndex: " + std::to_string(status->nCurrentTile), olc::WHITE);
		
			//current selection
			olc::Renderer::ptrPGE->DrawString({ 55, 100 }, "current body: " + targetBodyType.GetCurrentSelString(), olc::WHITE);
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
