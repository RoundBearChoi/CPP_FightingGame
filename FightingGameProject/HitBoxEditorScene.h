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
		UIElement leftSel;
		UIElement rightSel;
		
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

			leftSel.ptrDecal = ptrDecalLoader->GetDecal((int32_t)FighterSpriteType::editor_left_sel);
			leftSel.width = 18;
			leftSel.height = 24;
			leftSel.topLeft = { 5, 92 };

			rightSel.ptrDecal = ptrDecalLoader->GetDecal((int32_t)FighterSpriteType::editor_right_sel);
			rightSel.width = 18;
			rightSel.height = 24;
			rightSel.topLeft = { 5 + 24 + 1, 92 };

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
			
			//clickable UI
			playIcon.GreenTintOnHover(mousePos);
			leftSel.GreenTintOnHover(mousePos);
			rightSel.GreenTintOnHover(mousePos);

			if (playIcon.Clicked(mousePos, gameData))
			{
				fighter.stateController.currentState->animationController.UpdateTileIndex(true); //update dummy fighter frame
			}

			if (leftSel.Clicked(mousePos, gameData))
			{
				targetBodyType.PrevType();
			}

			if (rightSel.Clicked(mousePos, gameData))
			{
				targetBodyType.NextType();
			}

			//boxcolliders
			int32_t bodyIndex = (int32_t)targetBodyType.selectedType;

			if (bodyIndex < arrBoxCol.size())
			{
				if (gameData.key_t && gameData.key_y || !gameData.key_t && !gameData.key_y)
				{
					//double press (do nothing)
				}
				else if (gameData.key_t)
				{
					arrBoxCol[bodyIndex].RotateCounterClockwise();
				}
				else if (gameData.key_y)
				{
					arrBoxCol[bodyIndex].RotateClockwise();
				}

				if (gameData.key_g && gameData.key_h || !gameData.key_g && !gameData.key_h)
				{
					//double press (do nothing)
				}
				else if (gameData.key_g)
				{
					arrBoxCol[bodyIndex].IncreaseWidth(1);
				}
				else if (gameData.key_h)
				{
					arrBoxCol[bodyIndex].IncreaseHeight(1);
				}

				//resize, rotate, move boxcollider
				arrBoxCol[bodyIndex].SetQuad();
				arrBoxCol[bodyIndex].UpdateRotation();
				arrBoxCol[bodyIndex].UpdatePosition( //up down left right
					gameData.key_a,
					gameData.key_d,
					gameData.key_w,
					gameData.key_s);
			}

			for (int32_t i = 0; i < arrBoxCol.size(); i++)
			{
				arrBoxCol[i].SetQuad();
				arrBoxCol[i].UpdateRotation();
			}
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

				if (i == (int32_t)targetBodyType.selectedType)
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

			//selection arrows
			olc::Renderer::ptrPGE->DrawDecal(leftSel.topLeft, leftSel.ptrDecal, { 1.0f, 1.0f }, leftSel.tint);
			olc::Renderer::ptrPGE->DrawDecal(rightSel.topLeft, rightSel.ptrDecal, { 1.0f, 1.0f }, rightSel.tint);
		}
	};
}