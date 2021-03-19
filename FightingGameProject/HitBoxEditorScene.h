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
		
		std::vector<BoxCollider> boxColliders;
		TargetBodyType targetBodyType;

		int32_t nFrames = 0;
		int32_t nBodyParts = 0;

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

			//put all body parts into vector
			nFrames = fighter.stateController.currentState->animationController.TotalTiles();
			nBodyParts = (int32_t)BodyType::RIGHT_FOOT + 1;
			boxColliders.reserve(nBodyParts * nFrames);

			for (int32_t i = 0; i < nBodyParts * nFrames; i++)
			{
				int32_t x = (int32_t)floor(i / nBodyParts * nFrames) * 1;
				int32_t y = (i % nBodyParts) * -12;
				boxColliders.push_back(BoxCollider({ x, y }, 40, 50, 0.0f));
			}
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

			if (bodyIndex < boxColliders.size())
			{
				if (gameData.key_t && gameData.key_y || !gameData.key_t && !gameData.key_y)
				{
					//double press (do nothing)
				}
				else if (gameData.key_t)
				{
					boxColliders[bodyIndex].RotateCounterClockwise();
				}
				else if (gameData.key_y)
				{
					boxColliders[bodyIndex].RotateClockwise();
				}

				if (gameData.key_g && gameData.key_h || !gameData.key_g && !gameData.key_h)
				{
					//double press (do nothing)
				}
				else if (gameData.key_g)
				{
					boxColliders[bodyIndex].IncreaseWidth(1);
				}
				else if (gameData.key_h)
				{
					boxColliders[bodyIndex].IncreaseHeight(1);
				}

				//resize, rotate, move boxcollider
				boxColliders[bodyIndex].SetQuad();
				boxColliders[bodyIndex].UpdateRotation();
				boxColliders[bodyIndex].UpdatePosition( //up down left right
					gameData.key_a,
					gameData.key_d,
					gameData.key_w,
					gameData.key_s);
			}

			for (int32_t i = 0; i < boxColliders.size(); i++)
			{
				boxColliders[i].SetQuad();
				boxColliders[i].UpdateRotation();
			}
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 15 }, "HitBox Editor", olc::WHITE);

			RenderCenterMark(cam);

			//boxcolliders
			for (int32_t i = 0; i < boxColliders.size(); i++)
			{
				std::array<olc::vi2d, 4> quad;
				quad[0] = RelativeVector::GetPosition(boxColliders[i].Point0(), cam);
				quad[1] = RelativeVector::GetPosition(boxColliders[i].Point1(), cam);
				quad[2] = RelativeVector::GetPosition(boxColliders[i].Point2(), cam);
				quad[3] = RelativeVector::GetPosition(boxColliders[i].Point3(), cam);

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
			if ((int32_t)targetBodyType.selectedType < boxColliders.size())
			{
				olc::vi2d p0 = boxColliders[(int32_t)targetBodyType.selectedType].Point0();
				olc::vi2d p1 = boxColliders[(int32_t)targetBodyType.selectedType].Point1();
				olc::vi2d p2 = boxColliders[(int32_t)targetBodyType.selectedType].Point2();
				olc::vi2d p3 = boxColliders[(int32_t)targetBodyType.selectedType].Point3();

				olc::Renderer::ptrPGE->DrawString({ 0, 200 }, "point0: " + std::to_string(p0.x) + ", " + std::to_string(p0.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 12 }, "point1: " + std::to_string(p1.x) + ", " + std::to_string(p1.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 24 }, "point2: " + std::to_string(p2.x) + ", " + std::to_string(p2.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 36 }, "point3: " + std::to_string(p3.x) + ", " + std::to_string(p3.y), olc::WHITE);
			}

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