#pragma once

#include "Scene.h"
#include "UIElement.h"
#include "StringNotification.h"
#include "TargetBodyType.h"
#include "ColliderLoader.h"
#include "DummySelector.h"

//components
#include "AnimationRenderer.h"

namespace RB
{
	class HitBoxEditorScene : public Scene
	{
	private:
		DummySelector selector;
		TargetBodyType targetBodyType;

		UIElement playIcon;
		UIElement saveIcon;
		UIElement leftSel;
		UIElement rightSel;
		UIElement copyIcon0;
		UIElement copyIcon1;

		StringNotification saved;
		StringNotification copied0;
		StringNotification copied1;

		size_t nSelectedBodyIndex = 0;

		GroupComponent* ptrAnimationRenderer = nullptr;

	public:
		HitBoxEditorScene(GameDataFactory* gameDataFactory)
		{
			IF_COUT{ std::cout << "constructing HitBoxEditorScene" << std::endl; };

			DevSettings::renderMode = RenderMode::SPRITES_AND_DEBUG;
			_gameDataFactory = gameDataFactory;
			ptrAnimationRenderer = new AnimationRenderer();
		}

		~HitBoxEditorScene() override
		{
			delete ptrAnimationRenderer;

			IF_COUT{ std::cout << "destructing HitBoxEditorScene" << std::endl; };
		}

		void InitScene() override
		{
			playIcon.path = "PNG files/BoxColliderEditor/editor_playframe.png";
			playIcon.width = 54;
			playIcon.height = 42;
			playIcon.topLeft = { GameSettings::window_width / 2 - playIcon.width / 2, 10 };
			playIcon.spriteType = SpriteType::BOXCOLLIDER_EDITOR_UI;
			playIcon.SetHash();
			playIcon.SetDecal();

			saveIcon.path = "PNG files/BoxColliderEditor/editor_save.png";
			saveIcon.width = 33;
			saveIcon.height = 29;
			saveIcon.topLeft = { GameSettings::window_width - saveIcon.width - 15, 15 };
			saveIcon.spriteType = SpriteType::BOXCOLLIDER_EDITOR_UI;
			saveIcon.SetHash();
			saveIcon.SetDecal();

			leftSel.path = "PNG files/BoxColliderEditor/editor_left_sel.png";
			leftSel.width = 18;
			leftSel.height = 24;
			leftSel.topLeft = { 5, 92 };
			leftSel.spriteType = SpriteType::BOXCOLLIDER_EDITOR_UI;
			leftSel.SetHash();
			leftSel.SetDecal();

			rightSel.path = "PNG files/BoxColliderEditor/editor_right_sel.png";
			rightSel.width = 18;
			rightSel.height = 24;
			rightSel.topLeft = { 5 + 24 + 1, 92 };
			rightSel.spriteType = SpriteType::BOXCOLLIDER_EDITOR_UI;
			rightSel.SetHash();
			rightSel.SetDecal();

			copyIcon0.path = "PNG files/BoxColliderEditor/editor_copy.png";
			copyIcon0.width = 32;
			copyIcon0.height = 42;
			copyIcon0.topLeft = { GameSettings::window_width - copyIcon0.width - 15, 100 };
			copyIcon0.spriteType = SpriteType::BOXCOLLIDER_EDITOR_UI;
			copyIcon0.SetHash();
			copyIcon0.SetDecal();

			copyIcon1.path = "PNG files/BoxColliderEditor/editor_copy.png";
			copyIcon1.width = 32;
			copyIcon1.height = 42;
			copyIcon1.topLeft = { GameSettings::window_width - copyIcon1.width - 15, 200 };
			copyIcon1.spriteType = SpriteType::BOXCOLLIDER_EDITOR_UI;
			copyIcon1.SetHash();
			copyIcon1.SetDecal();

			//notifications
			saved.str = "saved!";
			saved.pos = { saveIcon.topLeft.x - 20, saveIcon.topLeft.y + 55 };
			saved.color = olc::RED;

			copied0.str = "copied!";
			copied0.pos = { copyIcon0.topLeft.x - 12, copyIcon0.topLeft.y + 61 };
			copied0.color = olc::RED;

			copied1.str = "copied!";
			copied1.pos = { copyIcon1.topLeft.x - 12, copyIcon1.topLeft.y + 61 };
			copied1.color = olc::RED;
		}

		void UpdateScene() override
		{
			GameData& gameData = *_gameDataFactory->GetGameData();

			//change dummy fighter
			if (gameData.key_left)
			{
				selector.Prev();
				gameData.key_left->processed = true;
			}
			else if (gameData.key_right)
			{
				selector.Next();
				gameData.key_right->processed = true;
			}

			//dummy fighter state
			selector.Current()->stateController.MakeStateTransition();
			
			State* s = selector.Current()->stateController.currentState;
			
			if (s != nullptr)
			{
				if (s->IsNew())
				{
					s->OnEnter(selector.Current()->objData, gameData);
					s->animationController.status.bPlayOnce = false;
				}
			}

			olc::vi2d mousePos = olc::Platform::ptrPGE->GetMousePos();
			
			//clickable UI
			playIcon.GreenTintOnHover(mousePos);
			saveIcon.GreenTintOnHover(mousePos);
			leftSel.GreenTintOnHover(mousePos);
			rightSel.GreenTintOnHover(mousePos);
			copyIcon0.GreenTintOnHover(mousePos);
			copyIcon1.GreenTintOnHover(mousePos);

			if (playIcon.Clicked(mousePos, gameData))
			{
				//update dummy fighter frame
				selector.Current()->stateController.currentState->animationController.NextTileIndex(true);
			}

			if (saveIcon.Clicked(mousePos, gameData))
			{
				std::string colliderFile = selector.Current()->stateController.currentState->animationController.GetColliderPath();
				ColliderLoader::SaveColliderData(selector.GetCollider(), colliderFile);

				saved.frames = 120 * 9;

				selector.Current()->stateController.currentState->UnloadColliderData();
			}

			if (copyIcon0.Clicked(mousePos, gameData))
			{
				selector.SyncFrames();
				copied0.frames = 120 * 9;
			}

			if (copyIcon1.Clicked(mousePos, gameData))
			{
				selector.SyncAll();
				copied1.frames = 120 * 9;
			}

			if (leftSel.Clicked(mousePos, gameData))
			{
				targetBodyType.PrevType();
			}

			if (rightSel.Clicked(mousePos, gameData))
			{
				targetBodyType.NextType();
			}

			if (gameData.key_np7)
			{
				gameData.key_np7->processed = true;
				targetBodyType.NextType();
			}

			if (gameData.key_np8)
			{
				gameData.key_np8->processed = true;
				targetBodyType.PrevType();
			}

			//boxcolliders
			int32_t currentTile = selector.Current()->stateController.currentState->animationController.status.nCurrentTile;
			nSelectedBodyIndex = (int32_t)targetBodyType.selectedType + (ColliderLoader::TotalBodyParts() * currentTile);

			if (nSelectedBodyIndex < selector.GetCollider().size())
			{
				if (gameData.key_t && gameData.key_y || !gameData.key_t && !gameData.key_y)
				{
					//double press (do nothing)
				}
				else if (gameData.key_t)
				{
					selector.GetCollider()[nSelectedBodyIndex].RotateCounterClockwise();
				}
				else if (gameData.key_y)
				{
					selector.GetCollider()[nSelectedBodyIndex].RotateClockwise();
				}

				if (gameData.key_g && gameData.key_h || !gameData.key_g && !gameData.key_h)
				{
					//double press (do nothing)
				}
				else if (gameData.key_g)
				{
					if (!gameData.key_shift)
					{
						selector.GetCollider()[nSelectedBodyIndex].IncreaseHeight(1);
					}
					else
					{
						selector.GetCollider()[nSelectedBodyIndex].DecreaseHeight(1);
					}
				}
				else if (gameData.key_h)
				{
					if (!gameData.key_shift)
					{
						selector.GetCollider()[nSelectedBodyIndex].IncreaseWidth(1);
					}
					else
					{
						selector.GetCollider()[nSelectedBodyIndex].DecreaseWidth(1);
					}
				}

				//resize, rotate, move boxcollider
				selector.GetCollider()[nSelectedBodyIndex].SetQuad(OffsetType::CENTER_CENTER);
				selector.GetCollider()[nSelectedBodyIndex].UpdateRotation();
				selector.GetCollider()[nSelectedBodyIndex].MovePosition( //up down left right
					gameData.key_a,
					gameData.key_d,
					gameData.key_w,
					gameData.key_s);
			}

			for (int32_t i = 0; i < selector.GetCollider().size(); i++)
			{
				selector.GetCollider()[i].SetQuad(OffsetType::CENTER_CENTER);
				selector.GetCollider()[i].UpdateRotation();
			}
		}

		void RenderObjs() override
		{
			olc::Renderer::ptrPGE->DrawString({ 0, 15 }, "HitBox Editor", olc::WHITE);

			RenderCenterMark(cam);

			//current boxcollider info
			if (nSelectedBodyIndex < selector.GetCollider().size())
			{
				olc::vi2d p0 = selector.GetCollider()[nSelectedBodyIndex].RelativePoint0();
				olc::vi2d p1 = selector.GetCollider()[nSelectedBodyIndex].RelativePoint1();
				olc::vi2d p2 = selector.GetCollider()[nSelectedBodyIndex].RelativePoint2();
				olc::vi2d p3 = selector.GetCollider()[nSelectedBodyIndex].RelativePoint3();

				olc::Renderer::ptrPGE->DrawString({ 0, 200 }, "point0: " + std::to_string(p0.x) + ", " + std::to_string(p0.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 12 }, "point1: " + std::to_string(p1.x) + ", " + std::to_string(p1.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 24 }, "point2: " + std::to_string(p2.x) + ", " + std::to_string(p2.y), olc::WHITE);
				olc::Renderer::ptrPGE->DrawString({ 0, 200 + 36 }, "point3: " + std::to_string(p3.x) + ", " + std::to_string(p3.y), olc::WHITE);
			}

			//current index # for animation
			olc::vi2d indexString = { playIcon.topLeft.x - 40, playIcon.topLeft.y + playIcon.height + 10 };
			AnimationStatus* status = selector.Current()->stateController.currentState->animationController.UpdateSource();
			olc::Renderer::ptrPGE->DrawString(indexString, "currentIndex: " + std::to_string(status->nCurrentTile), olc::WHITE);
			
			olc::vi2d fileName = indexString + olc::vi2d(0, 13);
			std::string currentFile = selector.Current()->stateController.currentState->animationController.GetColliderPath();
			olc::Renderer::ptrPGE->DrawString(fileName, currentFile, olc::WHITE);

			//current body part selection
			olc::Renderer::ptrPGE->DrawString({ 55, 100 }, "current body: " + targetBodyType.GetCurrentSelString(), olc::WHITE);

			//notifications
			saved.Show();
			copied0.Show();
			copied1.Show();
		}

		void RenderStates(bool update) override
		{
			//dummy fighter
			if (selector.Current() != nullptr)
			{
				ptrAnimationRenderer->Update(*selector.Current(), cam);
			}

			//play icon
			olc::Renderer::ptrPGE->DrawDecal(playIcon.topLeft, playIcon.ptrDecal, { 1.0f, 1.0f }, playIcon.tint);

			//save icon
			olc::Renderer::ptrPGE->DrawDecal(saveIcon.topLeft, saveIcon.ptrDecal, { 1.0f, 1.0f }, saveIcon.tint);
			olc::Renderer::ptrPGE->DrawString({ saveIcon.topLeft.x, saveIcon.topLeft.y + saveIcon.height + 4 }, "save");

			//copy icon 0
			olc::Renderer::ptrPGE->DrawDecal(copyIcon0.topLeft, copyIcon0.ptrDecal, { 1.0f, 1.0f }, copyIcon0.tint);
			olc::Renderer::ptrPGE->DrawString({ copyIcon0.topLeft.x - 120, copyIcon0.topLeft.y + copyIcon0.height + 5 }, "copy to other frames");

			//copy icon 1
			olc::Renderer::ptrPGE->DrawDecal(copyIcon1.topLeft, copyIcon1.ptrDecal, { 1.0f, 1.0f }, copyIcon1.tint);
			olc::Renderer::ptrPGE->DrawString({ copyIcon1.topLeft.x - 50, copyIcon1.topLeft.y + copyIcon1.height + 5 }, "copy to all");

			//selection arrows
			olc::Renderer::ptrPGE->DrawDecal(leftSel.topLeft, leftSel.ptrDecal, { 1.0f, 1.0f }, leftSel.tint);
			olc::Renderer::ptrPGE->DrawDecal(rightSel.topLeft, rightSel.ptrDecal, { 1.0f, 1.0f }, rightSel.tint);

			//boxcolliders
			size_t indexStart = selector.Current()->stateController.currentState->animationController.status.nCurrentTile * ColliderLoader::TotalBodyParts();

			for (size_t i = indexStart; i < indexStart + ColliderLoader::TotalBodyParts(); i++)
			{
				if (i == nSelectedBodyIndex)
				{
					selector.GetCollider()[i].Render(cam, { 0, 0 }, olc::RED);
				}
				else
				{
					selector.GetCollider()[i].Render(cam, { 0, 0 }, olc::BLUE);
				}
			}
		}
	};
}