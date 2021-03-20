#pragma once

#include "Scene.h"
#include "GameData.h"
#include "GameObj.h"
#include "UIElement.h"
#include "StringNotification.h"
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
		UIElement saveIcon;
		UIElement leftSel;
		UIElement rightSel;

		StringNotification saved;
		StringNotification savedFileName;
				
		std::vector<BoxCollider> boxColliders;
		TargetBodyType targetBodyType;

		int32_t nFrames = 0;
		int32_t nBodyParts = 0;
		int32_t bodyIndex = 0;

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
			fighter.stateController.CreateNewState<Fighter_0_Jab>();

			fighter.objData.SetOffsetType(OffsetType::BOTTOM_CENTER);
			fighter.objData.SetCreationID(1);
			fighter.objData.SetTransitionPermission(false);

			playIcon.ptrDecal = ptrDecalLoader->GetDecal((int32_t)FighterSpriteType::editor_playframe);
			playIcon.width = 54;
			playIcon.height = 42;
			playIcon.topLeft = { GameSettings::window_width / 2 - playIcon.width / 2, 10 };

			saveIcon.ptrDecal = ptrDecalLoader->GetDecal((int32_t)FighterSpriteType::editor_save);
			saveIcon.width = 33;
			saveIcon.height = 29;
			saveIcon.topLeft = { GameSettings::window_width - saveIcon.width - 15, 15 };

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
				int32_t y = -170 + (i % nBodyParts) * 12;
				boxColliders.push_back(BoxCollider({ x, y }, 40, 50, 0.0f));
			}

			LoadColliderData();

			//notifications
			saved.str = "saved!";
			saved.pos = { saveIcon.topLeft.x - 20, saveIcon.topLeft.y + 55 };
			saved.color = olc::RED;

			savedFileName.str = fighter.stateController.currentState->animationController.CollisionFileName();
			int32_t nameLength = (int32_t)savedFileName.str.length();
			savedFileName.pos = { GameSettings::window_width - (nameLength * 8), saveIcon.topLeft.y + 55 + 14 };
			savedFileName.color = olc::RED;
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
			saveIcon.GreenTintOnHover(mousePos);
			leftSel.GreenTintOnHover(mousePos);
			rightSel.GreenTintOnHover(mousePos);

			if (playIcon.Clicked(mousePos, gameData))
			{
				fighter.stateController.currentState->animationController.UpdateTileIndex(true); //update dummy fighter frame
			}

			if (saveIcon.Clicked(mousePos, gameData))
			{
				SaveColliderData();
				saved.frames = 120 * 9;
				savedFileName.frames = 120 * 9;
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
			bodyIndex = (int32_t)targetBodyType.selectedType + (nBodyParts * currentTile);

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
					if (!gameData.key_shift)
					{
						boxColliders[bodyIndex].IncreaseHeight(1);
					}
					else
					{
						boxColliders[bodyIndex].DecreaseHeight(1);
					}
				}
				else if (gameData.key_h)
				{
					if (!gameData.key_shift)
					{
						boxColliders[bodyIndex].IncreaseWidth(1);
					}
					else
					{
						boxColliders[bodyIndex].DecreaseWidth(1);
					}
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
			int32_t base = fighter.stateController.currentState->animationController.status.nCurrentTile * nBodyParts;
			for (int32_t i = base; i < base + nBodyParts; i++)
			{
				std::array<olc::vi2d, 4> quad;
				quad[0] = RelativeVector::GetPosition(boxColliders[i].Point0(), cam);
				quad[1] = RelativeVector::GetPosition(boxColliders[i].Point1(), cam);
				quad[2] = RelativeVector::GetPosition(boxColliders[i].Point2(), cam);
				quad[3] = RelativeVector::GetPosition(boxColliders[i].Point3(), cam);

				olc::Pixel color = olc::BLUE;

				if (i == bodyIndex)
				{
					color = olc::RED;
				}

				olc::Renderer::ptrPGE->DrawLine(quad[0], quad[1], color);
				olc::Renderer::ptrPGE->DrawLine(quad[1], quad[2], color);
				olc::Renderer::ptrPGE->DrawLine(quad[2], quad[3], color);
				olc::Renderer::ptrPGE->DrawLine(quad[3], quad[0], color);
			}

			//current boxcollider info
			if (bodyIndex < boxColliders.size())
			{
				olc::vi2d p0 = boxColliders[bodyIndex].Point0();
				olc::vi2d p1 = boxColliders[bodyIndex].Point1();
				olc::vi2d p2 = boxColliders[bodyIndex].Point2();
				olc::vi2d p3 = boxColliders[bodyIndex].Point3();

				olc::Renderer::ptrPGE->DrawString({ 0, 200 }, "point0: " + std::to_string(p0.x) + ", " + std::to_string(p0.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 12 }, "point1: " + std::to_string(p1.x) + ", " + std::to_string(p1.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 24 }, "point2: " + std::to_string(p2.x) + ", " + std::to_string(p2.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 36 }, "point3: " + std::to_string(p3.x) + ", " + std::to_string(p3.y), olc::WHITE);
			}

			//current index # for animation
			olc::vi2d indexString = { playIcon.topLeft.x - 40, playIcon.topLeft.y + playIcon.height + 10 };
			AnimationStatus* status = fighter.stateController.currentState->animationController.GetStatus();
			olc::Renderer::ptrPGE->DrawString(indexString, "currentIndex: " + std::to_string(status->nCurrentTile), olc::WHITE);
		
			//current body part selection
			olc::Renderer::ptrPGE->DrawString({ 55, 100 }, "current body: " + targetBodyType.GetCurrentSelString(), olc::WHITE);

			//notifications
			saved.Show();
			savedFileName.Show();
		}

		void RenderStates(bool update) override
		{
			//dummy fighter
			SheetRenderer::Render(ptrDecalLoader, &fighter, cam);

			//play icon
			olc::Renderer::ptrPGE->DrawDecal(playIcon.topLeft, playIcon.ptrDecal, { 1.0f, 1.0f }, playIcon.tint);

			//save icon
			olc::Renderer::ptrPGE->DrawDecal(saveIcon.topLeft, saveIcon.ptrDecal, { 1.0f, 1.0f }, saveIcon.tint);
			olc::Renderer::ptrPGE->DrawString({ saveIcon.topLeft.x, saveIcon.topLeft.y + saveIcon.height + 4 }, "save");

			//selection arrows
			olc::Renderer::ptrPGE->DrawDecal(leftSel.topLeft, leftSel.ptrDecal, { 1.0f, 1.0f }, leftSel.tint);
			olc::Renderer::ptrPGE->DrawDecal(rightSel.topLeft, rightSel.ptrDecal, { 1.0f, 1.0f }, rightSel.tint);
		}

		void LoadColliderData()
		{
			std::string path = "BoxColliderData/";
			std::string stateColliderFileName = fighter.stateController.currentState->animationController.CollisionFileName();

			if (stateColliderFileName.compare("none") != 0)
			{
				path += stateColliderFileName;

				FILE* pFile;
				size_t size = 0;

#pragma warning(disable: 4996) //disable visual studio warning
				pFile = fopen(path.c_str(), "r");
#pragma warning(default: 4996)

				if (pFile != nullptr)
				{
					std::fread(&size, sizeof(size_t), 1, pFile);

					if (size == boxColliders.size())
					{
						for (size_t i = 0; i < boxColliders.size(); i++)
						{
							int32_t x = 0;
							int32_t y = 0;
							int32_t width = 0;
							int32_t height = 0;
							float rotation = 0.0f;

							std::fread(&x, sizeof(int32_t), 1, pFile);
							std::fread(&y, sizeof(int32_t), 1, pFile);
							std::fread(&width, sizeof(int32_t), 1, pFile);
							std::fread(&height, sizeof(int32_t), 1, pFile);
							std::fread(&rotation, sizeof(float), 1, pFile);

							boxColliders[i].SetPosition(x, y);
							boxColliders[i].SetWidth(width);
							boxColliders[i].SetHeight(height);
							boxColliders[i].SetRotation(rotation);
						}
					}

					fclose(pFile);
				}
			}
		}

		void SaveColliderData()
		{
			std::string path = "BoxColliderData/";
			std::string stateColliderFileName = fighter.stateController.currentState->animationController.CollisionFileName();

			if (stateColliderFileName.compare("none") != 0)
			{
				path += stateColliderFileName;

				FILE* pFile;
				size_t vecSize = boxColliders.size();

#pragma warning(disable: 4996) //disable visual studio warning
				pFile = fopen(path.c_str(), "w");
#pragma warning(default: 4996)

				fwrite(&vecSize, sizeof(size_t), 1, pFile);
				
				for (size_t i = 0; i < boxColliders.size(); i++)
				{
					int32_t x = boxColliders[i].Position().x;
					int32_t y = boxColliders[i].Position().y;
					int32_t width = boxColliders[i].Width();
					int32_t height = boxColliders[i].Height();
					float rotation = boxColliders[i].Rotation();

					fwrite(&x, sizeof(int32_t), 1, pFile);
					fwrite(&y, sizeof(int32_t), 1, pFile);
					fwrite(&width, sizeof(int32_t), 1, pFile);
					fwrite(&height, sizeof(int32_t), 1, pFile);
					fwrite(&rotation, sizeof(float), 1, pFile);
				}
				
				fclose(pFile);
			}
		}
	};
}