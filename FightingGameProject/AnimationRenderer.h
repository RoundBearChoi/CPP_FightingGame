#pragma once
#include "olcPixelGameEngine.h"
#include "GroupComponent.h"
#include "Camera.h"
#include "AnimationStatus.h"
#include "DevSettings.h"
#include "SpriteType.h"

namespace RB
{
	class AnimationRenderer : public GroupComponent
	{
	public:
		void Update(GameObj& obj, Camera& cam) override
		{
			AnimationStatus* animationStatus = obj.stateController.currentState->animationController.UpdateSource();

			if (animationStatus == nullptr)
			{
				return;
			}

			obj.objData.SetAnimationIndex(animationStatus->nCurrentTile);

			int32_t x = obj.objData.GetPosition().x;
			int32_t y = obj.objData.GetPosition().y;
			int32_t width = obj.objData.GetSpriteSize().x;
			int32_t height = obj.objData.GetSpriteSize().y;

			std::array<olc::vf2d, 4> points;

			if (obj.objData.GetOffsetType() == OffsetType::BOTTOM_CENTER)
			{
				if (obj.objData.IsFacingRight())
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
			else if (obj.objData.GetOffsetType() == OffsetType::CENTER_CENTER)
			{
				if (obj.objData.IsFacingRight())
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

			SpriteType spriteType = obj.stateController.currentState->animationController.status.spriteType;
			size_t hash = obj.stateController.currentState->GetHash();
			olc::Decal* d = SpriteLoader::ptr->FindDecal(hash, (int32_t)spriteType);

			std::array<olc::vf2d, 4> relativePoints;
			relativePoints[0] = ScreenVector::GetScreenPosition(points[0], cam);
			relativePoints[1] = ScreenVector::GetScreenPosition(points[1], cam);
			relativePoints[2] = ScreenVector::GetScreenPosition(points[2], cam);
			relativePoints[3] = ScreenVector::GetScreenPosition(points[3], cam);

			if (DevSettings::renderMode == RenderMode::SPRITES_AND_DEBUG || DevSettings::renderMode == RenderMode::SPRITES_ONLY)
			{
				olc::Renderer::ptrPGE->DrawPartialWarpedDecal(d, relativePoints, animationStatus->sourcePos, animationStatus->sourceSize);
			}
		}
	};
}