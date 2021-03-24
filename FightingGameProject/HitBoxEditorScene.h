#pragma once

#include "Scene.h"
#include "GameData.h"
#include "GameObj.h"
#include "UIElement.h"
#include "StringNotification.h"
#include "BoxCollider.h"
#include "TargetBodyType.h"
#include "ColliderLoader.h"

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
		UIElement saveIcon;
		UIElement leftSel;
		UIElement rightSel;

		StringNotification saved;
				
		std::vector<BoxCollider> vecBoxColliders;
		TargetBodyType targetBodyType;

		int32_t nFrames = 0;
		int32_t nSelectedBodyIndex = 0;

	public:
		HitBoxEditorScene()
		{
			IF_COUT{ std::cout << "constructing HitBoxEditorScene" << std::endl; };
		}

		~HitBoxEditorScene() override
		{
			IF_COUT{ std::cout << "destructing HitBoxEditorScene" << std::endl; };
		}

		void InitScene() override
		{
			playIcon.path = "PNG files/BoxColliderEditor/editor_playframe.png";
			playIcon.SetHash();
			playIcon.SetDecal();
			playIcon.width = 54;
			playIcon.height = 42;
			playIcon.topLeft = { GameSettings::window_width / 2 - playIcon.width / 2, 10 };

			saveIcon.path = "PNG files/BoxColliderEditor/editor_save.png";
			saveIcon.SetHash();
			saveIcon.SetDecal();
			saveIcon.width = 33;
			saveIcon.height = 29;
			saveIcon.topLeft = { GameSettings::window_width - saveIcon.width - 15, 15 };

			leftSel.path = "PNG files/BoxColliderEditor/editor_left_sel.png";
			leftSel.SetHash();
			leftSel.SetDecal();
			leftSel.width = 18;
			leftSel.height = 24;
			leftSel.topLeft = { 5, 92 };

			rightSel.path = "PNG files/BoxColliderEditor/editor_right_sel.png";
			rightSel.SetHash();
			rightSel.SetDecal();
			rightSel.width = 18;
			rightSel.height = 24;
			rightSel.topLeft = { 5 + 24 + 1, 92 };

			//initial dummy
			fighter.stateController.CreateNewState<Fighter_0_WalkBack>();

			fighter.objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			fighter.objData.SetCreationID(1);

			InitTargetDummy();

			//notifications
			saved.str = "saved!";
			saved.pos = { saveIcon.topLeft.x - 20, saveIcon.topLeft.y + 55 };
			saved.color = olc::RED;
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
			}

			olc::vi2d mousePos = olc::Platform::ptrPGE->GetMousePos();
			
			//clickable UI
			playIcon.GreenTintOnHover(mousePos);
			saveIcon.GreenTintOnHover(mousePos);
			leftSel.GreenTintOnHover(mousePos);
			rightSel.GreenTintOnHover(mousePos);

			if (playIcon.Clicked(mousePos, gameData))
			{
				fighter.stateController.currentState->animationController.NextTileIndex(true); //update dummy fighter frame
			}

			if (saveIcon.Clicked(mousePos, gameData))
			{
				std::string colliderFile = fighter.stateController.currentState->animationController.GetColliderPath();
				ColliderLoader::SaveColliderData(vecBoxColliders, colliderFile);

				saved.frames = 120 * 9;

				fighter.stateController.currentState->UnloadColliderData();
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
			int32_t currentTile = fighter.stateController.currentState->animationController.status.nCurrentTile;
			nSelectedBodyIndex = (int32_t)targetBodyType.selectedType + (ColliderLoader::TotalBodyParts() * currentTile);

			if (nSelectedBodyIndex < vecBoxColliders.size())
			{
				if (gameData.key_t && gameData.key_y || !gameData.key_t && !gameData.key_y)
				{
					//double press (do nothing)
				}
				else if (gameData.key_t)
				{
					vecBoxColliders[nSelectedBodyIndex].RotateCounterClockwise();
				}
				else if (gameData.key_y)
				{
					vecBoxColliders[nSelectedBodyIndex].RotateClockwise();
				}

				if (gameData.key_g && gameData.key_h || !gameData.key_g && !gameData.key_h)
				{
					//double press (do nothing)
				}
				else if (gameData.key_g)
				{
					if (!gameData.key_shift)
					{
						vecBoxColliders[nSelectedBodyIndex].IncreaseHeight(1);
					}
					else
					{
						vecBoxColliders[nSelectedBodyIndex].DecreaseHeight(1);
					}
				}
				else if (gameData.key_h)
				{
					if (!gameData.key_shift)
					{
						vecBoxColliders[nSelectedBodyIndex].IncreaseWidth(1);
					}
					else
					{
						vecBoxColliders[nSelectedBodyIndex].DecreaseWidth(1);
					}
				}

				//resize, rotate, move boxcollider
				vecBoxColliders[nSelectedBodyIndex].SetQuad();
				vecBoxColliders[nSelectedBodyIndex].UpdateRotation();
				vecBoxColliders[nSelectedBodyIndex].UpdatePosition( //up down left right
					gameData.key_a,
					gameData.key_d,
					gameData.key_w,
					gameData.key_s);
			}

			for (int32_t i = 0; i < vecBoxColliders.size(); i++)
			{
				vecBoxColliders[i].SetQuad();
				vecBoxColliders[i].UpdateRotation();
			}
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 15 }, "HitBox Editor", olc::WHITE);

			RenderCenterMark(cam);

			//boxcolliders
			int32_t indexStart = fighter.stateController.currentState->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();
			
			for (int32_t i = indexStart; i < indexStart + ColliderLoader::TotalBodyParts(); i++)
			{
				if (i == nSelectedBodyIndex)
				{
					vecBoxColliders[i].Render(cam, olc::RED);
				}
				else
				{
					vecBoxColliders[i].Render(cam, olc::BLUE);
				}
			}

			//current boxcollider info
			if (nSelectedBodyIndex < vecBoxColliders.size())
			{
				olc::vi2d p0 = vecBoxColliders[nSelectedBodyIndex].Point0();
				olc::vi2d p1 = vecBoxColliders[nSelectedBodyIndex].Point1();
				olc::vi2d p2 = vecBoxColliders[nSelectedBodyIndex].Point2();
				olc::vi2d p3 = vecBoxColliders[nSelectedBodyIndex].Point3();

				olc::Renderer::ptrPGE->DrawString({ 0, 200 }, "point0: " + std::to_string(p0.x) + ", " + std::to_string(p0.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 12 }, "point1: " + std::to_string(p1.x) + ", " + std::to_string(p1.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 24 }, "point2: " + std::to_string(p2.x) + ", " + std::to_string(p2.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 36 }, "point3: " + std::to_string(p3.x) + ", " + std::to_string(p3.y), olc::WHITE);
			}

			//current index # for animation
			olc::vi2d indexString = { playIcon.topLeft.x - 40, playIcon.topLeft.y + playIcon.height + 10 };
			AnimationStatus* status = fighter.stateController.currentState->animationController.GetStatus();
			olc::Renderer::ptrPGE->DrawString(indexString, "currentIndex: " + std::to_string(status->nCurrentTile), olc::WHITE);
			
			olc::vi2d fileName = indexString + olc::vi2d(0, 13);
			std::string currentFile = fighter.stateController.currentState->animationController.GetColliderPath();
			olc::Renderer::ptrPGE->DrawString(fileName, currentFile, olc::WHITE);

			//current body part selection
			olc::Renderer::ptrPGE->DrawString({ 55, 100 }, "current body: " + targetBodyType.GetCurrentSelString(), olc::WHITE);

			//notifications
			saved.Show();
		}

		void RenderStates(bool update) override
		{
			//dummy fighter
			SheetRenderer::Render(&fighter, cam);

			//play icon
			olc::Renderer::ptrPGE->DrawDecal(playIcon.topLeft, playIcon.ptrDecal, { 1.0f, 1.0f }, playIcon.tint);

			//save icon
			olc::Renderer::ptrPGE->DrawDecal(saveIcon.topLeft, saveIcon.ptrDecal, { 1.0f, 1.0f }, saveIcon.tint);
			olc::Renderer::ptrPGE->DrawString({ saveIcon.topLeft.x, saveIcon.topLeft.y + saveIcon.height + 4 }, "save");

			//selection arrows
			olc::Renderer::ptrPGE->DrawDecal(leftSel.topLeft, leftSel.ptrDecal, { 1.0f, 1.0f }, leftSel.tint);
			olc::Renderer::ptrPGE->DrawDecal(rightSel.topLeft, rightSel.ptrDecal, { 1.0f, 1.0f }, rightSel.tint);
		}

		void InitTargetDummy()
		{
			//put all body parts into vector
			vecBoxColliders.clear();

			nFrames = fighter.stateController.currentState->animationController.TotalTiles();
			ColliderLoader::SetFighterBodyParts(vecBoxColliders, nFrames);

			std::string colliderFile = fighter.stateController.currentState->animationController.GetColliderPath();
			ColliderLoader::LoadColliderData(vecBoxColliders, colliderFile);
		}
	};
}