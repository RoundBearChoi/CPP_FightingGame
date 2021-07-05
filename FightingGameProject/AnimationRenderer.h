#pragma once
#include "olcPixelGameEngine.h"
#include "IGroupComponent.h"
#include "AnimationStatus.h"
#include "DevSettings.h"
#include "SpriteType.h"
#include "DummySelector.h"

namespace RB
{
	class AnimationRenderer : public IGroupComponent
	{
	private:
		DummySelector* _dummySelector = nullptr;
		std::vector<ObjBase*>* _vecTargets = nullptr;
		Camera* _camera = nullptr;

	public:
		//for gamescene
		AnimationRenderer(std::vector<ObjBase*>* vecTargets, Camera* camera)
		{
			_vecTargets = vecTargets;
			_camera = camera;
		}

		//for hitboxeditorscene
		AnimationRenderer(DummySelector* dummySelector, Camera* camera)
		{
			_dummySelector = dummySelector;
			_camera = camera;
		}

		void Update() override
		{
			if (_dummySelector != nullptr)
			{
				Render(_dummySelector->Current());
			}
			else
			{
				std::vector<ObjBase*>& vec = *_vecTargets;

				for (size_t i = 0; i < vec.size(); i++)
				{
					if (vec[i] != nullptr)
					{
						Render(vec[i]);
					}
					else
					{
						IF_COUT{ std::cout << "null gameobj.. skipping render.." << std::endl; }
					}
				}
			}
		}

		void Render(ObjBase* obj)
		{
			AnimationStatus* animationStatus = obj->GetCurrentState()->animationController.UpdateSource();

			if (animationStatus == nullptr)
			{
				return;
			}

			obj->objData.SetAnimationIndex(animationStatus->nCurrentTile);

			int32_t x = obj->objData.GetPosition().x;
			int32_t y = obj->objData.GetPosition().y;
			int32_t width = obj->objData.GetSpriteSize().x;
			int32_t height = obj->objData.GetSpriteSize().y;

			std::array<olc::vf2d, 4> points;

			if (obj->objData.GetOffsetType() == OffsetType::BOTTOM_CENTER)
			{
				if (obj->objData.IsFacingRight())
				{
					points[0] = { (float)x - (float)width / 2.0f, (float)y - (float)height };
					points[1] = { (float)x - (float)width / 2.0f, (float)y };
					points[2] = { (float)x + (float)width / 2.0f, (float)y };
					points[3] = { (float)x + (float)width / 2.0f, (float)y - (float)height };
				}
				else
				{
					points[0] = { (float)x + (float)width / 2.0f, (float)y - (float)height };
					points[1] = { (float)x + (float)width / 2.0f, (float)y };
					points[2] = { (float)x - (float)width / 2.0f, (float)y };
					points[3] = { (float)x - (float)width / 2.0f, (float)y - (float)height };
				}
			}
			else if (obj->objData.GetOffsetType() == OffsetType::CENTER_CENTER)
			{
				if (obj->objData.IsFacingRight())
				{
					points[0] = { (float)x - (float)width / 2.0f, (float)y - (float)height / 2.0f };
					points[1] = { (float)x - (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[2] = { (float)x + (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[3] = { (float)x + (float)width / 2.0f, (float)y - (float)height / 2.0f };
				}
				else
				{
					points[0] = { (float)x + (float)width / 2.0f, (float)y - (float)height / 2.0f };
					points[1] = { (float)x + (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[2] = { (float)x - (float)width / 2.0f, (float)y + (float)height / 2.0f };
					points[3] = { (float)x - (float)width / 2.0f, (float)y - (float)height / 2.0f };
				}
			}

			SpriteType spriteType = obj->GetCurrentState()->animationController.status.spriteType;
			size_t hash = obj->GetCurrentState()->GetHash();
			olc::Decal* d = SpriteLoader::ptr->FindDecal(hash, (int32_t)spriteType);

			std::array<olc::vf2d, 4> relativePoints;
			relativePoints[0] = ScreenVector::GetScreenPosition(points[0], *_camera);
			relativePoints[1] = ScreenVector::GetScreenPosition(points[1], *_camera);
			relativePoints[2] = ScreenVector::GetScreenPosition(points[2], *_camera);
			relativePoints[3] = ScreenVector::GetScreenPosition(points[3], *_camera);

			if (DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG || DevSettings::renderMode == RenderMode::SPRITES_ONLY)
			{
				olc::Renderer::ptrPGE->DrawPartialWarpedDecal(d, relativePoints, animationStatus->sourcePos, animationStatus->sourceSize);
			}
		}
	};
}