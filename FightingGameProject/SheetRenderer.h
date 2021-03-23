#pragma once
#include "olcPixelGameEngine.h"
#include "SpriteLoader.h"
#include "GameObj.h"
#include "AnimationStatus.h"
#include "Camera.h"
#include "Renderer.h"

namespace RB
{
	class SheetRenderer
	{
	public:
		static void Render(GameObj* obj, Camera& cam)
		{
			AnimationStatus* animationStatus = obj->stateController.currentState->animationController.GetStatus();

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

			SpriteType spriteType = obj->stateController.currentState->animationController.status.spriteType;
			size_t hash = obj->stateController.currentState->GetHash();
			olc::Decal* d = SpriteLoader::ptr->FindDecal(hash, (int32_t)spriteType);

			std::array<olc::vf2d, 4> relativePoints;
			relativePoints[0] = RelativeVector::GetPosition(points[0], cam);
			relativePoints[1] = RelativeVector::GetPosition(points[1], cam);
			relativePoints[2] = RelativeVector::GetPosition(points[2], cam);
			relativePoints[3] = RelativeVector::GetPosition(points[3], cam);

			RENDERER->DrawPartialWarpedDecal(d, relativePoints, animationStatus->sourcePos, animationStatus->sourceSize);
		}
	};
}